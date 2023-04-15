# **Http 메소드에 따른 요청 메세지 처리 방법**

## **GET 메소드**
> HTTP GET 메서드는 특정한 리소스를 가져오도록 요청합니다. GET 요청은 데이터를 가져올 때만 사용해야 합니다.

## **POST 메소드**
> HTTP POST 메서드는 서버로 데이터를 전송합니다. 요청 본문의 유형은 Content-Type 헤더로 나타냅니다.

### **예제**
**요청**
> POST / HTTP/1.1 </br>
> Host: foo.com </br>
> Content-Type: application/x-www-form-urlencoded </br>
> Content-Length: 13 </br>
> </br>
> say=Hi&to=Mom </br>

**응답**
> POST /test.html HTTP/1.1 </br>
> Host: example.org </br>
> Content-Type: multipart/form-data;boundary="boundary" </br>
>  </br>
> --boundary </br>
> Content-Disposition: form-data; name="field1" </br>
>  </br>
> value1 </br>
> --boundary </br>
> Content-Disposition: form-data; name="field2"; filename="example.txt" </br>
>  </br>
> value2 </br>
> --boundary-- </br>


## **DELETE 메소드**
> HTTP DELETE 메서드는 지정한 리소스를 삭제합니다.

### **예제**
**요청**
> DELETE /file.html HTTP/1.1

**응답**

DELETE 메서드를 성공적으로 적용한 후에 사용할 수 있는 응답 상태 코드는 다음과 같이 몇 가지가 있습니다.

> 1. 아마도 명령을 성공적으로 수행할 것 같으나 아직은 실행하지 않은 경우 202 (Accepted) 상태 코드.
> 2. 명령을 수행했고 더 이상 제공할 정보가 없는 경우 204 (No Content) 상태 코드.
> 3. 명령을 수행했고 응답 메시지가 이후의 상태를 설명하는 경우 200 (OK) 상태 코드.

> HTTP/1.1 200 OK </br>
> Date: Wed, 21 Oct 2015 07:28:00 GMT </br>
>  </br>
> &#60;html&#62; </br>
>   &#60;body>&#62; </br>
>     &#60;h1&#62;File deleted.&#60;/h1&#62; </br>
>   &#60;/body&#62; </br>
> &#60;/html&#62; </br>