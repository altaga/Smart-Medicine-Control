# Smart-Medicine-Control

<img src="https://i.ibb.co/yy4t5gn/Logo.png" width="1000">

Always use technology to improve the world, if you are a black hat or gray hat hacker please abstain at this point ......... or at least leave your star to make me feel less guilty XP.

# Table of contents

* [Introduction](#introduction)
* [Materials](#materials)
* [Connection Diagram](#connection-diagram)
* [RFID Introduction](#rfid-introduction)
* [Google Colab Project](#google-colab-project)
* [CloudMQTT Setup](#cloudmqtt-setup)
* [ArduinoIDE Board Setup](#arduinoide-board-setup)
* [Library Setup](#library-setup)
* [Files Setup](#files-setup)
* [Boards Setup](#boards-setup)
* [Node-Red Setup](#node-red-setup)
* [The Final Product](#the-final-product)
* [Future Rollout](#future-rollout)
* [References](#references)

## Introduction:

Inside hospitals, pharmacies and clinics we can find lots of inventories, but one of the most important is the one in charge of storing drugs or medicine. Inside the hospital, the consumption of medicine and drugs in relation with control of inventory is one of the most important and difficult tasks to perform. Nevertheless  there are hospitals with very robust and technologically advanced systems, even outdated systems for filling out paper applications. However, until today, we find seldom solutions for this problem that integrate and use ML and AI models.

On this premise we decided to create an inventory control system that learns through AI models the medication entry patterns, in order to be able to make predictions about which medications could be ordered in the following orders and the urgency. The records will enter through RFID on the medication provided.

A couple of solutions we can find in the market are:

Link: https: //www.clearstreamrfid.com/pricing.htm $2500 dollars.

This product is only an RFID reading hardware for inventory control, which is a bit more suitable for department stores. Note that it uses no AI.

Link: https://id-integration.com/rfid-starter-kits-for-asset-tracking $ 499 - $ 4999

Provides hardware and even integrations with software, but of course none with an AI implementation.

Our solution will be very different, because we will be able to carry out AI implementations through medication registries, which will have an RFID stamp. These will be fundamental for saving orders on medications, avoiding lack of medications or overstocking and continuously improving the system of Hospitals, clinics and pharmacy inventories.

## Materials:

Hardware:
- SparkFun RedBoard Artemis ATP                    x1.
https://www.sparkfun.com/products/15442/
- ESP32                                            x1.
https://www.adafruit.com/product/3405
- SparkFun RFID Qwiic Reader                       x1.
https://www.sparkfun.com/products/15191
- RFID Reader ID-12LA (125kHz)                     x1.
https://www.sparkfun.com/products/11827
- RFID Tag (125kHz)                                x2.
https://www.sparkfun.com/products/14325
- Qwiic Cable - 100mm                              x1.
https://www.sparkfun.com/products/14427
- Standed-Core Wire                                x1.
https://www.adafruit.com/product/2987
- Breadboard PCB                                   x1.
https://www.amazon.com/dp/B081K1278N/ref=cm_sw_em_r_mt_dp_U_5x.gEb2Z02Q3B

Software:
- Arduino IDE.
- Google Colab.
- Cloud MQTT.

## Connection Diagram:

This is the connection diagram of the system:

<img src="https://i.ibb.co/nrPRQmG/Diagram.png" width="800">

## RFID Introduction:

RFID (radio frequency identification) is a form of wireless communication that incorporates the use of electromagnetic or electrostatic coupling in the radio frequency portion of the electromagnetic spectrum to uniquely identify an object, animal or person. Use cases for RFID technology include healthcare, manufacturing, inventory management, shipping, retail sales and home use.

<img src="https://i.ibb.co/ncDW95n/Untitled-1.png" width="800">

This scheme is applicable to any RFID reader in the market but it is more efficient to use the scheme for our project.

<img src="https://ccllabel.com/wp-content/uploads/2016/05/healthcare_smart_products_rfid_blue.jpg" width="800">

In this case we use this technology for medical inventory.

## Google Colab Project:

To make our project as compatible as possible with any computer or even a mobile phone, we design it to run in Google Colab. Colaboratory is a Google research project created to help disseminate machine learning education and research. It's a Jupyter notebook environment that requires no setup to use and runs entirely in the cloud.

https://github.com/altaga/Smart-Medicine-Control/blob/master/Google%20Colab%20Model%20Creator/SmartMedicineControl.ipynb

The first step in creating a model for microcontrollers will be to use the latest version of TensorFlow.

<img src = "https://i.ibb.co/bNCF93B/image.png" width = "700">

We import the following libraries for the code to function properly.

<img src = "https://i.ibb.co/dm3htqH/image.png" width = "700">

Then we check the TF version we have.

<img src = "https://i.ibb.co/s5yncPV/image.png" width = "700">

We import the dataset

<img src = "https://i.ibb.co/4Tqj1HD/image.png" width = "700">

Obtaining the data and turning it into a Pandas dataframe.

This is a dataframe of the entry and exit of medications in a hospital in one year, with each row meaning one day of the year.

*   Mo1 = Output Medicine 1
*   Mo2 = Output Medicine 2
*   Mo3 = Output Medicine 3
*   Mo4 = Output Medicine 4
*   Mo5 = Output Medicine 5
*   Mi1 = Input Medicine 1
*   Mi2 = Input Medicine 2
*   Mi3 = Input Medicine 3
*   Mi4 = Input Medicine 4
*   Mi5 = Input Medicine 5
*   U = Urgency

<img src = "https://i.ibb.co/ZJGVfL5/image.png" width = "700">

We check the data to see that we have incoming and outgoing stock. As usual we can see that the hospital, having a bad inventory system, has an over-stock. With more incoming and outgoing medications, however we have to be able to fix that through our AI.

<img src = "https://i.ibb.co/m6qhP4X/image.png" width = "700">

We take the first 5 input data as the output stock and the next 6 as the 5 input medications and their urgency.

We measure urgency on a scale of 0 - 5.

<img src = "https://i.ibb.co/7Gn5NKR/image.png" width = "700">

We create our model based on an input of 5 neurons and an output of 6.

<img src = "https://i.ibb.co/Q9cYnhD/image.png" width = "700">

We train our model by performing 1000 cycles with training data, this value can vary to obtain different results, but modifying it can cause an underfit or overfit of the model.

<img src = "https://i.ibb.co/h7CqTvS/image.png" width = "700">

We perform the precision and loss graphs of the model to verify that it works correctly, these graphs are a standard in AI models, I always recommend to perform them in all its models.

<img src = "https://i.ibb.co/mtfv6Bc/image.png" width = "400"><img src = "https://i.ibb.co/bzwnJYw/image.png" width = "400">

We randomly select an entry and we evaluate it with our normal model and our model converted to TF lite, as we can see the model behaves very similar to the complete TF model.

<img src = "https://i.ibb.co/0ymSjVR/image.png" width = "600">

As a last step we will convert the model into a vector that can be read by the mircrocontroller, do not close the window because we will have to input this code into the microcontroller.

<img src = "https://i.ibb.co/jyj8PF3/image.png" width = "700">

See the model executedin its Jupyter notebook with explanations in full at:

https://github.com/altaga/Smart-Medicine-Control/blob/master/Google%20Colab%20Model%20Creator/SmartMedicineControl.ipynb

Here ends the part related to the AI model, the next section is the configuration of your machine to compile and flash the program on the board.

## CloudMQTT Setup:

Create an account in Cloud MQTT.

https://www.cloudmqtt.com/

Copy the credentials of "Server", "User", "Password" and "Port".

<img src = "https://i.ibb.co/s9wR395/image.png" width = "1000">

## ArduinoIDE Board Setup:

To add board support, start Arduino and open the Preferences window (File > Preferences). 

<img src = "https://i.ibb.co/kmSRjtP/image.png" width = "700">

Now copy and paste the following URL into the 'Additional Boards Manager URLs' input field:

    https://raw.githubusercontent.com/sparkfun/Arduino_Boards/master/IDE_Board_Manager/package_sparkfun_index.json
    
Note: if you do not have ESP32 installed as a board, also add the following url separating them with a comma **, **:

    https://dl.espressif.com/dl/package_esp32_index.json
    
<img src = "https://i.ibb.co/Zdgvc56/image.png" width = "700">

Open the Boards Manager window by selecting Tools > Board, scroll to the top of the board list, and select Boards Manager.

<img src = "https://i.ibb.co/Tr43M49/image.png" width = "700">

Type "sparkfun" (without quotes) into the "filter your search" field, you will see options to install SparkFun's Apollo3 and AVR board files. Click in the desired box, and click the "Install" button that appears. Once installed, the boards will appear at the bottom of the board list.(Note: I use version 1.0.17 for this tutorial)

<img src = "https://i.ibb.co/0yqTN4x/image.png" width = "700">

Note: If you do not have ESP32 installed, search for "ESP32" and press install button for the “ESP32 by Espressif Systems“

## Library Setup:

Open Sketch > Include Library > Manage Libraries... 

<img src = "https://i.ibb.co/Wkjv19Q/image.png" width = "700">

Install the "Arduino_TensorFlowLite library by TensorFlow Authors Version 1.15.0-ALPHA"

<img src = "https://i.ibb.co/VD2vr2v/image.png" width = "700">

## Files Setup:

In this case we will use arduino programs, that of the ESP32 and that of the RedBoard, both are contained within the Arduino files folder, so you do not have to do anything more than open them just as they are once you have downloaded the project.

<img src = "https://i.ibb.co/B4rbcxp/Move.png" width = "700">

## Boards Setup:

Inside the ArduinoIDE we will open the file inside the Arduino Files> RedBoardAI> RedBoardAI.ino folder, once there we will select the RedBoard as the objective of the program in Tools> Board> SparkFun RedBoard Artemis ATP.

<img src = "https://i.ibb.co/yWrdPYp/image.png" width = "700">

Press the compile button to make sure everything works correctly.

<img src = "https://i.ibb.co/vJ6q1Ch/image.png" width = "700">

We return to our project within Google Colab and copy the model and its size.

<img src = "https://i.ibb.co/jz70zpf/image.png" width = "700">

Now we will go to the data.cpp file and paste the model into the **my_model** variable and the size into the **my_model_len** variable.

<img src = "https://i.ibb.co/ydjZ9NT/image.png" width = "700">

The following setup will be done on ESP32, we only have to open the file and replace the credentials with yours.

<img src = "https://i.ibb.co/3MH3dfL/image.png" width = "700">

If everything works fine, you should be able to flash the programs on each of the boards.

## Node-Red Setup:

Node Red is a tool for NodeJS where we can integrate services easily, without code and, of course, create excellent dashboards.

NodeJS installation guide: https://www.guru99.com/download-install-node-js.html

NodeRED installation guide: https://nodered.org/docs/getting-started/windows

NodeRED installation guide: https://flows.nodered.org/node/node-red-dashboard

The file "flows.json" in the folder "Node-RED Flow", has all the information to import the flow into your NodeRED.

<img src = "https://i.ibb.co/c11ZJT8/image.png" width = "400">
<img src = "https://i.ibb.co/nBL3M23/image.png" width = "400">

Once that is done we will edit the MQTT node to enter our credentials.

<img src = "https://i.ibb.co/58BpP35/image.png" width = "600">

Set Server and Port.

<img src = "https://i.ibb.co/wdzbztp/image.png" width = "600">

Set User and Password.

<img src = "https://i.ibb.co/cDjySLr/image.png" width = "600">

If everything works fine press the "Deploy" button and enter the following URL to check the Dashboard.

http://localhost:1880/ui

<img src = "https://i.ibb.co/Cs3v3Gr/image.png" width = "800">

## Project assembly:

All:

<img src="https://i.ibb.co/FwcSxz5/20200202-150308.png" width="800">
<img src="https://i.ibb.co/qYt7qxX/20200202-150745.png" width="800">
<img src="https://i.ibb.co/XbvpzD2/20200202-150758.png" width="800">
<img src="https://i.ibb.co/CWcXS5P/20200202-150819.png" width="800">
<img src="https://i.ibb.co/Yd3kCv8/20200202-150850.png" width="800">
<img src="https://i.ibb.co/Z1ndQs4/20200202-150905.png" width="800">
<img src="https://i.ibb.co/5xypYGs/20200202-151253.png" width="800">
<img src="https://i.ibb.co/NFDXRZ5/20200202-151313.png" width="800">
<img src="https://i.ibb.co/DMMjmVQ/20200202-151333.png" width="800">

Complete system:

<img src="https://i.ibb.co/YZ7v4Y8/Final.png" width="800">

### Our Epic DEMO:

Video: Click on the image

[![Rehab](https://i.ibb.co/yy4t5gn/Logo.png)](https://youtu.be/fDEJnKJJC_w)

Sorry github does not allow embed videos.

## Commentary:
We are quite satisfied with how this project came about, and we think that the implementation of AI and Machine learning at the edge is quite novel for this use case. By working in the healthcare industry (both in developed and underdeveloped countries) we have seen which klind of problems are more recurrent. Among those is the rising cost of healthcare and among that we can count the poor inventory systems that we have. They have been exploited for quite a while now generating even more problems and it is an area where AI can shine by reducing costs and granting the users valuable information. For a prototype this project has great potential as it only lacks a little in terms of design both Industrial and Electronics but we are quite amazed in how the Redboard performed and we look forward to keep experinmenting with hardware like this one.

## References:
(1) http://article.sapub.org/10.5923.j.mm.20130301.01.html

https://www.sparkfun.com/

http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.15.8571&rep=rep1&type=pdf
