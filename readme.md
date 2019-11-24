# Post Raspberry Pi data to your mobile phone through IFTTT

This program allows you to get a pin status of the Raspberry Pi and post to IFTTT webhook.
This can be modified to send any data you want, from a website or an application running in your Raspberry Pi.
More info at: [en.jorgeacortes.com](http://en.jorgeacortes.com/2015/12/getting-mobile-notifications-from-raspberry-pi-gpio/)

## Config
You have to change the event to the one you defined on IFTTT and enter your IFTTT webhook key.

Value2 and Value3 are fixed in this program, you can modify it and send any data you wish following the Value1 example.

## Dependencies
 - Libcurl
 - wiringPi
