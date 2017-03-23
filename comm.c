#include "comm.h"
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

void send_data_curl(double Leq[])
{
	char postdata[200]="data=", temp[30];
	int i;
	CURL *curl;
	CURLcode res;
	for(i=0; i<8; i++)	//this for loop prepare the post string
	{
		sprintf(temp, (i==7)?"%.2f":"%.2f;", Leq[i]);	//there is a ternary operator
		strcat(postdata, temp);		//Append temp to postdata
	}
	printf("%s\n", postdata);
	//postdata is rey
	curl_global_init(CURL_GLOBAL_ALL);	 //globally initiate curl
        curl = curl_easy_init();	 //make a curl handler
        if(curl)
        {
		//Set URL of server page
                curl_easy_setopt(curl, CURLOPT_URL, URL);
		//Set post data
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata);
		//Perform a submit
                res = curl_easy_perform(curl);
                if(res != CURLE_OK)	//if the server side is negative
                {
                        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			curl_easy_strerror(res);
                }
                curl_easy_cleanup(curl);	//output error
	}
	curl_global_cleanup();	//globally ending curl

}
