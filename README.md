Below is the information on the pin configuration and files

File MainUnitCode_C

Pin configuration


                        +---------+
pin 36 (red act led)   -|         |- pin 1 button digital in
pin 37 (grn act led)   -|         |- pin 2 peer brn digital in
pin 38 (blu act led)   -|         |-
pin 39 (K act led)     -|         |- pin 10 Power A sensor in
pin 15 (red act led)   -|         |- pin 11 Power B sensor in
pin 16 (red act led)   -|         |-
pin 17 (red act led)   -|         |-
pin 18 (red act led)   -|         |-
                       -|         |-
                       -|         |-
                        +---------+
               


When I tried to use the page for the setup, here is how the HTTP response after post looked like (The characters here are from the client)

POST / HTTP/1.1
Host: 192.168.0.31
Connection: keep-alive
Content-Length: 296
Cache-Control: max-age=0
Origin: http://192.168.0.31
Upgrade-Insecure-Requests: 1
DNT: 1
Content-Type: application/x-www-form-urlencoded
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.0.0 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
Referer: http://192.168.0.31/
Accept-Encoding: gzip, deflate
Accept-Language: en-US,en;q=0.9

Email=ahmeed%40email.com&Password=passsword+here&dvc_group=home&SSID=ssidhere&wpassword=ssidpassword&DVC1=ac1&MAC1=00%3A12%3A34%3A56%3A78%3A90&DVC2=Device+1&MAC2=&DVC3=Device+3&MAC3=&DVC4=Device+4&MAC4=&DVC5=Device+5&MAC5=&DVC6=Device+6&MAC6=&DVC7=Device+7&MAC7=&DVC8=Device+8&MAC8=&submit=Submit


*) HTML file is stored separately. It is called setuppage.h. When running on Arduino IDE, the setup file needs to be included in a separate tab. We do this by clicking on the top right chevron and then we get a comment to add file name. We have to name it setuppage.h, then the software will call for the raw file as an include.

*) If the HTTP header is a POST, then continue until you see submit=Submit instead of double empty lines.

*) Algorithm for taking in parameters: 1) Search for &Password, and carve out from position 7 (skipping Email=) and until that &Password. 2) Search for &dvc_group= and take section from &Password= position to this position, ... etc.
