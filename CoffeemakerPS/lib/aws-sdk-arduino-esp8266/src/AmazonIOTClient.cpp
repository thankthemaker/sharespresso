#include "AmazonIOTClient.h"
#include "AWSFoundationalTypes.h"
#include <stdlib.h>
#include "Utils.h"

AmazonIOTClient::AmazonIOTClient() : AWSClient4() {
    this->awsService = "iotdata";
    this->contentType = "application/json";
    this->signedHeaders = "content-length;content-type;host;x-amz-content-sha256;x-amz-date";
    this->uri = "/";
    this->queryString = "";
    this->httpS = true;
}

const char* AmazonIOTClient::update_shadow(MinimalString shadow, ActionError& actionError) {
    actionError = NONE_ACTIONERROR;

    this->method = "POST";
    char* request = createRequest(shadow);
    // return request;
    const char* response = sendData(request);
    return response;
}

const char* AmazonIOTClient::get_shadow(ActionError& actionError) {
    actionError = NONE_ACTIONERROR;

    this->method = "GET";
	MinimalString shadow = "";
    char* request = createRequest(shadow);
    // return request;
    const char* response = sendData(request);
    return response;
}
