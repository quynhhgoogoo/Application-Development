#include <stdio.h>
#include <curl/curl.h>

int main(void)
{
	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_ALL);	//globally initiate curl
	curl = curl_easy_init();	//make a curl handler
	if(curl)
	{
		//Set URL of server page
		curl_easy_setopt(curl, CURLOPT_URL, "http://www.cc.puv.fi/~e1601128/curl.php");
		//Set post data
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "value=100&from=e1601128");
		//Perform a submit
		res = curl_easy_perform(curl);
		if(res != CURLE_OK)	//if the server side is negative
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
} 

