# Smart-Medicine-Control

<img src="https://i.ibb.co/yy4t5gn/Logo.png" width="500">

Always use technology to improve the world, if you are a black hat or gray hat hacker please abstain at this point ......... or at least leave your star to make me feel less guilty XP.

# Table of contents

* [Introduction](#introduction)
* [Materials](#materials)
* [Connection Diagram](#connection-diagram)
* [RFID Introduction](#rfid-introduction)
* [Google Colab Project](#google-colab-project)
* [AI Developing](#brainium-setup)
* [CloudMQTT Setup](#cloudmqtt-setup)
* [Laptop Setup](#laptop-setup)
* [Arm Setup](#arm-setup)
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

My solution will be very different, because we will be able to carry out AI implementations through medication registries, which will have an RFID stamp. These will be fundamental for saving orders on medications, avoiding lack of medications or overstocking and continuously improving the system of Hospitals, clinics and pharmacy inventories.

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

Para realizar nuestro proyecto lo mas compatible posible con cualquier computadora o incluso un movil, realizamos nuestro proyecto en Google Colab. Colaboratory is a Google research project created to help disseminate machine learning education and research. It's a Jupyter notebook environment that requires no setup to use and runs entirely in the cloud.

https://github.com/altaga/Smart-Medicine-Control/blob/master/Google%20Colab%20Model%20Creator/SmartMedicineControl.ipynb

El primer paso para crear un modelo se AI aterrizado para microcontroladores sera utilizar la version de TensorFlow mas reciente.

<img src = "https://i.ibb.co/bNCF93B/image.png" width = "500">

Importamos las siguientes librerias para el buen funcionamiento del codigo.

<img src = "https://i.ibb.co/dm3htqH/image.png" width = "500">

Revisamos la version de TensorFlow que tenemos.

<img src = "https://i.ibb.co/s5yncPV/image.png" width = "500">

Importamos el dataset para realizar el modelo.

<img src = "https://i.ibb.co/4Tqj1HD/image.png" width = "500">

Obtaining the data and turning it into a Pandas dataframe.

This is a dataframe of the entry and exit of medications in a hospital in one year, with each row is one day of the year.

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

<img src = "https://i.ibb.co/ZJGVfL5/image.png" width = "500">

Revisamos la data para ver que tenemos stock de entrada y de salida, como es normal podemos ver que el hospital al tener un mal sistema de inventario tenemos un sobre stock, con mas medicamentos de entrada que de salida, sin embargo nosotros tenemos que poder arreglar eso mediante nuestra AI.

<img src = "https://i.ibb.co/m6qhP4X/image.png" width = "500">

Tomamos los primeros 5 datos de entrada como el stock de salida y los siguientes 6 como los 5 medicamentos de entrada y su urgencia.

La urgencia la medimos en una escala de 0 - 5.

<img src = "https://i.ibb.co/7Gn5NKR/image.png" width = "500">

Creamos nuestro modelo basandonos una entrada de 5 neuronas y una salida de 6.

<img src = "https://i.ibb.co/Q9cYnhD/image.png" width = "500">

Entrenamos a nuestro modelo realizando 1000 ciclos con los datos de entrenamiento, este valor pueden variarlo para obtener diferentes resultados, pero modificarlo puede provocar un underfit u overfit del modelo.

<img src = "https://i.ibb.co/h7CqTvS/image.png" width = "500">

Realizamos las graficas de precicion y perdida del modelo para verificar que funcione correctamente, estas graficas son un estandard en los modelos de AI, recomiendo siempre relizarlas en todos sus modelos.

<img src = "https://i.ibb.co/mtfv6Bc/image.png" width = "500"><img src = "https://i.ibb.co/bzwnJYw/image.png" width = "500">

### Widget Configuration:

Press the button to create the widget.

<img src = "https://i.ibb.co/zZSCtkK/image.png" width = "500">

We assign the model to the device.

<img src = "https://i.ibb.co/wC98Vs3/image.png" width = "500">

We create a widget as shown in the image.

<img src = "https://i.ibb.co/tD5b4F3/image.png" width = "500">

We finish the widget.

<img src = "https://i.ibb.co/dkB1cJ0/image.png" width = "500">

We will get a result like the following.

<img src = "https://i.ibb.co/2shLmdn/image.png" width = "500">

### Obtaining Credentials.

Save External access token and User ID.

<img src = "https://i.ibb.co/DCcdzCP/image.png" width = "500">

## CloudMQTT Setup:

Create an account in Cloud MQTT.

https://www.cloudmqtt.com/

Copy the credentials of "Server", "User", "Password" and "Port".

<img src = "https://i.ibb.co/s9wR395/image.png" width = "1000">

## Laptop Setup:

Install Python Anaconda so that you can easily manipulate the MQTT broker, this had to be done because the Arduino library ESP32 for MQTT does not accept connectivity such as Websocket.

https://www.anaconda.com/distribution/

Then install this library:

    pip install paho-mqtt

Download the file Python Files, open "MQTTRehab.py" and put your credentials.

## Arm Setup:

Follow this diagram without making a mistake, IF YOU DON'T CONNECT IT WELL YOU CAN DO A SHORT CIRCUIT:

<img src="https://hackster.imgix.net/uploads/attachments/942233/68747470733a2f2f692e6962622e636f2f4832344451384e2f41524d2d62622e706e67.png" width="800">

After connecting all program the ESP32 with the code in the "Arduino Files" folder.

<img src="https://www.e-ika.com/images/thumbs/0005376_placa-esp32-wifi-bluetooth_600.jpeg" width="800">

Open the "ESP32ARMRehab.ino" file and enter the CloudMQTT credentials.

    const char* ssid = "YOURSSID";
    const char* password =  "YOURPASS";
    const char* mqttServer = "m12.cloudmqtt.com";
    const int mqttPort = 12345;
    const char* mqttUser = "YOURCLOUDMQTTUSER";
    const char* mqttPassword = "YOURCLOUDMQTTPASS";

## The Final Product:

Robotic Arm:

<img src="https://i.ibb.co/X3JNNLB/DSC00056-2.jpg" width="800">
<img src="https://i.ibb.co/HHM2DQ1/DSC00059-2.jpg" width="800">

ESP32 Arm Driver:

<img src="https://i.ibb.co/mJ73KNs/DSC00068.jpg" width="800">

Brainium Module:

<img src="https://i.ibb.co/cFZrYdJ/DSC00061-2.jpg" width="800">
<img src="https://i.ibb.co/kgds0Xn/DSC00062-2.jpg" width="800">
<img src="https://i.ibb.co/xFm1f0T/DSC00063-2.jpg" width="800">

Complete system:

<img src="https://i.ibb.co/dMb7c6V/DSC00066-2.jpg" width="800">

### Our Epic DEMO:

Video: Click on the image
[![Rehab](https://i.ibb.co/Bjg48mh/Brainium-Rehab.png)](https://youtu.be/GYoLvldvk-s)

Sorry github does not allow embed videos.

## Future Rollout:

 inventa algo

## References:

Links 
