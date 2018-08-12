/*
 * main.c
 *
 *	Get data from RPi and make a post to IFTTT
 *
 *  Created on: Aug 12, 2018
 *      Author: Jorge A. Cortés
 */

/*Includes*/
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <curl/curl.h>

/*Config*/
#define STRING_MAX_SIZE 255
#define VALUE1_PIN 11
static const char key[]="";	//Your IFTTT webhook key
static const char event1[]="iot_data_1";			//Your IFTTT webhook event as defined in your applet

/*Declarations*/
static uint16_t read_value();
static void post(const char event[STRING_MAX_SIZE], char payload[STRING_MAX_SIZE]);
static void payload_create(uint16_t value1, uint16_t value2, uint16_t value3, char payload[STRING_MAX_SIZE]);


/*Main function*/
int main(void)
{
	char payload[STRING_MAX_SIZE];
	uint16_t value1=0;

	value1=read_value();
	payload_create(value1,200,0,payload);
	post(event1,payload);

	return 0;
}


static uint16_t read_value(){
	wiringPiSetup();
	pinMode(VALUE1_PIN,INPUT);
	return digitalRead(VALUE1_PIN);
}

/*Fixed way to generate the payload in the IFTTT format*/
static void payload_create(uint16_t value1, uint16_t value2, uint16_t value3, char payload[STRING_MAX_SIZE]){
	sprintf(payload,"value1=%d&value2=%d&value3=%d",value1,value2,value3);
}

/*Method based on CURL to post the data to IFTTT*/
static void post(const char event[STRING_MAX_SIZE], char payload[STRING_MAX_SIZE]){

	CURL *curl;
	CURLcode res;
	char curl_url[STRING_MAX_SIZE];

	/* In windows, this will init the winsock stuff */
	//curl_global_init(CURL_GLOBAL_ALL);

	/* get a curl handle */
	curl = curl_easy_init();
	if(curl) {
		/* First set the URL that is about to receive our POST. This URL can
		   just as well be a https:// URL if that is what should receive the
		   data. */
		sprintf(curl_url,"https://maker.ifttt.com/trigger/%s/with/key/%s",event,key);
		curl_easy_setopt(curl, CURLOPT_URL, curl_url);
		/* Now specify the POST data */
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload);

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if(res != CURLE_OK)
		  fprintf(stderr, "curl_easy_perform() failed: %s\n",
				  curl_easy_strerror(res));

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}
