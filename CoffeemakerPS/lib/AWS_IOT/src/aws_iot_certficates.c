/*
 * Copyright 2010-2015 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Additions Copyright 2016 Espressif Systems (Shanghai) PTE LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

/**
 * @file aws_iot_certifcates.c
 * @brief File to store the AWS certificates in the form of arrays
 */

#ifdef __cplusplus
extern "C" {
#endif

const char aws_root_ca_pem[] = {"-----BEGIN CERTIFICATE-----\n\
MIIE0zCCA7ugAwIBAgIQGNrRniZ96LtKIVjNzGs7SjANBgkqhkiG9w0BAQUFADCB\n\
yjELMAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQL\n\
ExZWZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJp\n\
U2lnbiwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxW\n\
ZXJpU2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0\n\
aG9yaXR5IC0gRzUwHhcNMDYxMTA4MDAwMDAwWhcNMzYwNzE2MjM1OTU5WjCByjEL\n\
MAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQLExZW\n\
ZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJpU2ln\n\
biwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxWZXJp\n\
U2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0aG9y\n\
aXR5IC0gRzUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCvJAgIKXo1\n\
nmAMqudLO07cfLw8RRy7K+D+KQL5VwijZIUVJ/XxrcgxiV0i6CqqpkKzj/i5Vbex\n\
t0uz/o9+B1fs70PbZmIVYc9gDaTY3vjgw2IIPVQT60nKWVSFJuUrjxuf6/WhkcIz\n\
SdhDY2pSS9KP6HBRTdGJaXvHcPaz3BJ023tdS1bTlr8Vd6Gw9KIl8q8ckmcY5fQG\n\
BO+QueQA5N06tRn/Arr0PO7gi+s3i+z016zy9vA9r911kTMZHRxAy3QkGSGT2RT+\n\
rCpSx4/VBEnkjWNHiDxpg8v+R70rfk/Fla4OndTRQ8Bnc+MUCH7lP59zuDMKz10/\n\
NIeWiu5T6CUVAgMBAAGjgbIwga8wDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8E\n\
BAMCAQYwbQYIKwYBBQUHAQwEYTBfoV2gWzBZMFcwVRYJaW1hZ2UvZ2lmMCEwHzAH\n\
BgUrDgMCGgQUj+XTGoasjY5rw8+AatRIGCx7GS4wJRYjaHR0cDovL2xvZ28udmVy\n\
aXNpZ24uY29tL3ZzbG9nby5naWYwHQYDVR0OBBYEFH/TZafC3ey78DAJ80M5+gKv\n\
MzEzMA0GCSqGSIb3DQEBBQUAA4IBAQCTJEowX2LP2BqYLz3q3JktvXf2pXkiOOzE\n\
p6B4Eq1iDkVwZMXnl2YtmAl+X6/WzChl8gGqCBpH3vn5fJJaCGkgDdk+bW48DW7Y\n\
5gaRQBi5+MHt39tBquCWIMnNZBU4gcmU7qKEKQsTb47bDN0lAtukixlE0kF6BWlK\n\
WE9gyn6CagsCqiUXObXbf+eEZSqVir2G3l6BFoMtEMze/aiCKm0oHw0LxOXnGiYZ\n\
4fQRbxC1lfznQgUy286dUV4otp6F01vvpX1FQHKOtw5rDgb7MzVIcbidJ4vEZV8N\n\
hnacRHr2lVz2XTIIM6RUthg/aFzyQkqFOFSDX9HoLPKsEdao7WNq\n\
-----END CERTIFICATE-----\n"};

const char certificate_pem_crt[] = {"-----BEGIN CERTIFICATE-----\n\
MIIDWjCCAkKgAwIBAgIVAIoVpXC8RA8Pb0ru4Vv3Vz0m2eKtMA0GCSqGSIb3DQEB\n\
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n\
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0xODA0MDUxNTUy\n\
MTZaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n\
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC17HX4NCnKaKARDmya\n\
LAafBN4GBl0zXtw2liOtRDcbLmuz7zytQIXgyQShGbIqHZxyNh/QHhZrjNBI86/j\n\
Tdz1cwYqhipYXPpMP323IoLFhuf3KOTMP2nNMKgIg5MIMctnDv41OfUMq/ZBrS3K\n\
WAdX5D0NCOJ8Z34YBMw+dh/KKM3m8p+sKEdAiAWTjtzeuxncsuKE2NjzE+MeItdE\n\
PXbAEvm3E/8E89t20XkBxlWOiXGd7qZGQY5FCmkO6tgp+ELUUnLcy8xyzHqZDPKY\n\
jRUd/y10drhhv/NDUpqVDQRRexclDCkT9aVHv86Vcl3rJ/Yx9iRNnO87JsPIiARP\n\
UEFzAgMBAAGjYDBeMB8GA1UdIwQYMBaAFDSbNzMw1tXRoR/oLSw+Pe6++L5TMB0G\n\
A1UdDgQWBBSP278GsmN7vrTWXYcTesRhkLhcoTAMBgNVHRMBAf8EAjAAMA4GA1Ud\n\
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAn3vdrrioOgOrmR7qyVP/vedS\n\
YvD58fApWw3G1s6fDqlgDbkykvXs6yaZee6yHtcU+fo2k7Iea22gnfcygRuH687X\n\
narBS6qUDTPkeV0blYjuISVuuvARyiDs4PcxgLi/w7663GucqX2MXsvr10SoNrSK\n\
EktYSt4Zl46X1nAP4qYM1AswWUtkZ4bfht5SZPgfwqLEAQtH9M58WEVluFOKF6ia\n\
CCaUnSL9SfOuQhBknAVAUVYIpRHbzRFYrw+hxXAKWeUFK/i5FInSMYvjTow4htAX\n\
Pwq7F2pltMu5LrZS1qU4sbghWbaiq3gf5b0vgKBkbICmR57K7vUYXDgjp9VvAw==\n\
-----END CERTIFICATE-----\n"};

const char private_pem_key[] = {"-----BEGIN RSA PRIVATE KEY-----\n\
MIIEpAIBAAKCAQEAtex1+DQpymigEQ5smiwGnwTeBgZdM17cNpYjrUQ3Gy5rs+88\n\
rUCF4MkEoRmyKh2ccjYf0B4Wa4zQSPOv403c9XMGKoYqWFz6TD99tyKCxYbn9yjk\n\
zD9pzTCoCIOTCDHLZw7+NTn1DKv2Qa0tylgHV+Q9DQjifGd+GATMPnYfyijN5vKf\n\
rChHQIgFk47c3rsZ3LLihNjY8xPjHiLXRD12wBL5txP/BPPbdtF5AcZVjolxne6m\n\
RkGORQppDurYKfhC1FJy3MvMcsx6mQzymI0VHf8tdHa4Yb/zQ1KalQ0EUXsXJQwp\n\
E/WlR7/OlXJd6yf2MfYkTZzvOybDyIgET1BBcwIDAQABAoIBAQCsQKGOiq2LJjdx\n\
DuxLqiX2yWAD6mCy9D2kPdK4Cx/2T6TQ8VPNY4ufxBXrB+6HLBRmm9LRdruZx/Gr\n\
MXk3yxDNIsUS3IgZtKeWLIO3NCkIKG1Yu9KvhdeC3nAr55D/ME68XRjbgu4Auo3n\n\
r7bsoR8K3GPmBKSWUFO3IEvXVHdTLGhhN/oPeeRvS8S2qaL6/3emDnwHbxzWc1R/\n\
5nfClE71OQarRSw3MxBCd/FeiJWZU4wkNLk3kETyKlx5ahZdJmPlnCHwdgMpY78l\n\
lIEum2VFQPU0Do/xYNac3RVIzmWk8uDE/1w59thBODKB0sqnma0DsDt3jhd6Fder\n\
xaaMf0RBAoGBAOLkSdRJPDE10jZhyW/LMrSz8nB92IugLd0wOLqpuY7hj/VNp98R\n\
MfSRVxUEByBmQxusisdcZZK6F0mEfxSjPta5WlYPoRBTt2/6sVIykd1FhJiLtGnB\n\
7k/guQYEtKJyj5z9L6Xf1rewFMbW3/u1KqyifzVtyBkuMtZKVVMDwbeTAoGBAM1D\n\
TfdYjyOKKra5aYk549BN/fw4QUghsWPh9ooGL8Ft/ijvBfzXs+1NFc+6EGWlDu2h\n\
avG6kABE0JkshaokG/bDer6PYBRGCA5ppuKQET2YCZlEBCNIL5FZhE3yscnVBDcB\n\
X75xy/zvWHjFVAIVwnSBYyiuiqrr/R3AJrG7WbqhAoGBAJhQ4S9eKsZudzyC0RP3\n\
uYaN9weFtEWntqJyqOLG5gcBbf8jrrqVdI/WsjsthQs/G3YMku3bHWUvAEseY6Gb\n\
JahIrlhwDZREXzURetDPmhSNgsJVpzwIMM/28L8VkZ4sgjTF06Lrbd3Km2gRADSe\n\
HpPeUr+vf1FILmClbjpYn0d5AoGAcTjs6sEIw7vU79G6ax1pkl9S+Cs3p0geh0//\n\
JAdhlDrN9VpTXTLGZuEcZObnYIn5gA6H5SrZf6x1u+gZGs6sNiOBs1d20fgHPZv9\n\
l/+L4wPYV5hzB9srketk1XJHq2M63fR+EZjHwo9rp8KBIl1KU+WDAs+0Ya+mgSCa\n\
t3L2fcECgYBM4YwWseaAEpzOBeqG+HN6GtZ4j5Gi7oWf4pNe3L+IsGOnCwK3qp3Z\n\
x6QWTRvyRWn3QBfbrV97dV7HKSEAHd8cFRhHQYV+7BUBCdZs5cxXOGQLI0TV1mBs\n\
JGdiLAtTWCASQJxs+RiCa/sLyjIWqVpchse53MJy/hkLj3bTVObuZQ==\n\
-----END RSA PRIVATE KEY-----\n"};


#ifdef __cplusplus
}
#endif
