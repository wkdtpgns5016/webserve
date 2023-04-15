


## **4. Http 메세지 객체**
> **Http 메세지 개요**
> + 4-1. Http 메세지 요소
>    + StartLine
>    + RequestLine
>    + StatusLine
> + 4-2. Http 메세지
>    + HttpMessage
>    + HttpRequestMessage
>    + HttpResponseMessage
### **4-1. Http 메세지 요소**

**class StartLine**
> Start Line 추상화 객체

**Attribute**
> | 타입 | 이름 | 접근 제한     | 설명 |
> |:----------|:----------|:----------|:----------:|
> | string | _http_version | protected | http 버전 |
> |  |  |           |  |

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | string getHttpVersion(void) const | public | http version getter |
> | virtual bool isVaild(void) = 0 | public | 유효성 검사 가상 메소드 |
> | virtual string getString(void) = 0 | public | 문자열 반환 가상 메소드 |

------------------------------------------------

**class RequestLine**
> Request Line 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
> | string | _http_method | protected | http 버전 |
> | string | _request_target | protected | 요청 타켓 |
> |  |  |  |  |

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | string getHttpMethod(void) const | public | http method getter |
> | string getRequestTarget(void) const | public | request target getter |
> | virtual bool isVaild(void) = 0 | public | 유효성 검사 가상 메소드 |
> | virtual string getString(void) = 0 | public | 문자열 반환 가상 메소드 |

------------------------------------------------

**class StatusLine**
> Status Line 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:
> | int | _status_code | protected | 상태 코드 |
> | string | _status_message | protected | 상태 메세지 |
> |  |  |  |  |

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | string getStatusCode(void) const | public | status code getter |
> | string getStatusMessage(void) const | public | status message getter |
> | virtual bool isVaild(void) = 0 | public | 유효성 검사 가상 메소드 |
> | virtual string getString(void) = 0 | public | 문자열 반환 가상 메소드 |

-----------------------------------------------------

### **4-2. Http 요청 메세지**
**class HttpMessage**
> Http Message 추상화 객체

**Attribute**
> | 타입 | 이름 | 접근 제한     | 설명 |
> |:----------|:----------|:----------|:----------:|
> | map&#60;string, string&#62; | _headers | protected | http 헤더 |
> | string | _message_body | protected   | 메세지 바디 |

**Method**
> | 함수 원형                                              | 접근 제한   |         설명          |
> |:---------------------------------------------------|:--------|:-------------------:|
> | void setHeader(string)                             | private |   http 헤더 초기화 메소드   |
> | map&#60;string, string&#62; getHeaders(void) const | public  | http header getter  |
> | string getMessageBody(void) const                  | public  | message body getter |
> | virtual bool isVaild(void) = 0                     | public  |    유효성 검사 가상 메소드    |
> | virtual string getString(void) = 0                 | public  |    문자열 반환 가상 메소드    |

------------------------------------------------

**HttpRequestMessage**
> Http Request Message 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
> | RequestLine | _start_line | private | 시작 줄 |
> |  |  |  |  |

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | string getRequestLine(void) const | public | request line getter |
> | bool isVaild(void) | public | 유효성 검사 메소드 |
> | string getString(void) | public | 문자열 반환 메소드 |

------------------------------------------------

**HttpResponseMessage**
> Http Response Message 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
> | StatusLine | _start_line | private | 시작 줄 |
> |  |  |  |  |

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | bool isVaild(void) | public | 유효성 검사 메소드 |
> | string getString(void) | public | 문자열 반환 메소드 |

---------------------------------------------------

