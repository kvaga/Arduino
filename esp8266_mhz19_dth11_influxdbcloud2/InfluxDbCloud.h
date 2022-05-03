#ifndef _INFLUXDB_CLOUD_H_
#define _INFLUXDB_CLOUD_H_
/**
 * 
 * InfluxDBCloud.h: InfluxDB Client for Arduino
 * 
 * MIT License
 * 
 * Copyright (c) 2020 InfluxData
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

// Certificate Authority of InfluxData Cloud 2 servers
const char InfluxDbCloud2CACert[] PROGMEM =  R"EOF( 
-----BEGIN CERTIFICATE-----
MIIFVjCCBD6gAwIBAgISBEqETUzcf46feIkQkkNlixxuMA0GCSqGSIb3DQEBCwUA
MDIxCzAJBgNVBAYTAlVTMRYwFAYDVQQKEw1MZXQncyBFbmNyeXB0MQswCQYDVQQD
EwJSMzAeFw0yMjAzMTIxMjA0MzBaFw0yMjA2MTAxMjA0MjlaMDMxMTAvBgNVBAMT
KGV1cm9wZS13ZXN0MS0xLmdjcC5jbG91ZDIuaW5mbHV4ZGF0YS5jb20wggEiMA0G
CSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDiB64ZnzGxW1uCLbGzt/kYO7dJlDhl
IH19X2JQtRLLKIkV9pRex/3puwURrORWZy5xJHuvrwXvQ8eH3EoQ7rYADfXhf9F3
hCgTn3UWC8C1bcD9h/DtqY9JFVqvZNEXerIirzPYO6qoxMJDqQlPo9csX1sZ1BbC
eArHQdPIPh24UOKyid8aG7Q8mLECmV5yebA/z0KYmZbLxyz5O4DXlB/kKl4j3E5Q
XTsQxqeOA0OB2Ho8gN+hJgJc0ruX6BHFwdDAiRmTrsrsCaqQA1rf2hSaNQWUqGgM
qgifAF17rEVpb+kpOGDU0Nmvuix8YE7AWYKf1OcEAr4qPFaDwEvnYRR9AgMBAAGj
ggJjMIICXzAOBgNVHQ8BAf8EBAMCBaAwHQYDVR0lBBYwFAYIKwYBBQUHAwEGCCsG
AQUFBwMCMAwGA1UdEwEB/wQCMAAwHQYDVR0OBBYEFGPoE7uWrWAQLDsMzurTAOeY
4Bp8MB8GA1UdIwQYMBaAFBQusxe3WFbLrlAJQOYfr52LFMLGMFUGCCsGAQUFBwEB
BEkwRzAhBggrBgEFBQcwAYYVaHR0cDovL3IzLm8ubGVuY3Iub3JnMCIGCCsGAQUF
BzAChhZodHRwOi8vcjMuaS5sZW5jci5vcmcvMDMGA1UdEQQsMCqCKGV1cm9wZS13
ZXN0MS0xLmdjcC5jbG91ZDIuaW5mbHV4ZGF0YS5jb20wTAYDVR0gBEUwQzAIBgZn
gQwBAgEwNwYLKwYBBAGC3xMBAQEwKDAmBggrBgEFBQcCARYaaHR0cDovL2Nwcy5s
ZXRzZW5jcnlwdC5vcmcwggEEBgorBgEEAdZ5AgQCBIH1BIHyAPAAdwBByMqx3yJG
ShDGoToJQodeTjGLGwPr60vHaPCQYpYG9gAAAX9+OwN1AAAEAwBIMEYCIQD9gvwi
ez8gnvuA8tr6dlN2Doi2X9mgDoEVCdgS2Y7iYAIhAPfeZgtNsl9T+yVX8k87HkHM
qD/CgPFGUpVBhOUPsgiNAHUARqVV63X6kSAwtaKJafTzfREsQXS+/Um4havy/HD+
bUcAAAF/fjsDlAAABAMARjBEAiAF2TpiWL7FD4B4KZbn95MO2G6VmroC5RoBdx0S
npFbGAIgEHOZ05HdrD5dNSMNiPj3SgiFoZ/1s3/yfrLq/2otDv0wDQYJKoZIhvcN
AQELBQADggEBACYVzQBochEIV6vcCrAYXOo8+aIMrSyPqcbnIJgYUE3MJJPVfLQw
Sve8WRD0I//kqU4aaey6WM2sazLzNEYlD28+v02mpIBqD7ooXMD5o3COUsBC/WjL
CYx/jRx5uzYQv9bC4v6KPwNYuhkMqxrUL8BIN8nm0+P0xldL+VBdYWfkE88/hvHh
qXeomHohmgZG/DOsgogum2+C01TkQnG2wFoBvWm90HtZ73zXLkeRVXMTYE8jwPyv
I7TLw8WWOmvAOCHc8qcsl+UsPjg2fWCVdyE4dx1RCYTpc2AHA7D6HczcNmSH/7Jc
rtEHl5sGERZDLqOON6uGvUZIHlwT4oAuC9w=
-----END CERTIFICATE-----
)EOF";

#endif //_INFLUXDB_CLOUD_H_