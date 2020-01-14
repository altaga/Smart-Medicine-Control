/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

// Undefine predefined Arduino max/min defs so they don't conflict with std methods
#if defined(min)
#undef min
#endif

#if defined(max)
#undef max
#endif

#define RFID_ADDR 0x7D // Default I2C address 

#include <TensorFlowLite.h>
#include "tensorflow/lite/experimental/micro/kernels/micro_ops.h"
#include "tensorflow/lite/experimental/micro/micro_error_reporter.h"
#include "tensorflow/lite/experimental/micro/micro_interpreter.h"
#include "tensorflow/lite/experimental/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"
#include "data.h"
#include <Wire.h> 
#include "SparkFun_Qwiic_Rfid.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 4); //RX, TX - Any pins can be used
Qwiic_Rfid myRfid(RFID_ADDR);

const int intPin = 18; 
char med[11]={0,0,0,0,0,0,0,0,0,0,0};
String tag; 

// Globals, used for compatibility with Arduino-style sketches.
namespace {
tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;

// Create an area of memory to use for input, output, and intermediate arrays.
// The size of this will depend on the model you're using, and may need to be
// determined by experimentation.
constexpr int kTensorArenaSize = 6 * 1024;
uint8_t tensor_arena[kTensorArenaSize];
}  // namespace

// The name of this function is important for Arduino compatibility.
void setup() {
  Serial.begin(115200);
  Wire.begin(); 
  mySerial.begin(115200);

  if(myRfid.begin())
    Serial.println("Ready to scan some tags!"); 
  else
    Serial.println("Could not communicate with the Qwiic RFID Reader!!!"); 

  // Put the interrupt pin in a known HIGH state. 
   pinMode(intPin, INPUT_PULLUP); 
   
  for(int k =0 ; k<11;k++)
  {
    mySerial.print(med[k]); 
  }  
  
  // Set up logging. Google style is to avoid globals or statics because of
  // lifetime uncertainty, but since this has a trivial destructor it's okay.
  // NOLINTNEXTLINE(runtime-global-variables)
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  // Map the model into a usable data structure. This doesn't involve any
  // copying or parsing, it's a very lightweight operation.
  model = tflite::GetModel(my_model);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    error_reporter->Report(
        "Model provided is schema version %d not equal "
        "to supported version %d.",
        model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

  // Pull in only the operation implementations we need.
  // This relies on a complete list of all the ops needed by this graph.
  // An easier approach is to just use the AllOpsResolver, but this will
  // incur some penalty in code space for op implementations that are not
  // needed by this graph.
  //
  // tflite::ops::micro::AllOpsResolver resolver;
  // NOLINTNEXTLINE(runtime-global-variables)
  static tflite::MicroMutableOpResolver resolver;

  // Build an interpreter to run the model with.
  static tflite::MicroInterpreter static_interpreter(
      model, resolver, tensor_arena, kTensorArenaSize,
      error_reporter);
  interpreter = &static_interpreter;

  // Allocate memory from the tensor_arena for the model's tensors.
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    error_reporter->Report("AllocateTensors() failed");
    return;
  }

  // Get information about the memory area to use for the model's input.
  input = interpreter->input(0);
  output = interpreter->output(0);
}

// The name of this function is important for Arduino compatibility.
void loop() {

  if(digitalRead(intPin) == LOW){
    tag = myRfid.getTag();
    if(tag=="1080975179113")
    {
      int num = random(0, 4 + 1);
      if(num>4)
      {
        num=4;
      }
      med[num]++;
      for(int k =0 ; k<11;k++)
      {
       mySerial.print(med[k]); 
      }     
    }
    else if(tag=="9605810869115")
    {
       AI();
       for(int k =0 ; k<11;k++)
      {
       mySerial.print(med[k]); 
      }   
    }
    delay(500);
  }

    
  
}

void AI (void)
{
    for (int u = 0; u < 5; u++) {
      input->data.f[u] = med[u];
    }
   
    TfLiteStatus invoke_status = interpreter->Invoke();

    for(int j = 0 ; j < 6 ; j++)
    {
    float out = output->data.f[j];
    med[j]=int(out);
    }   
}
