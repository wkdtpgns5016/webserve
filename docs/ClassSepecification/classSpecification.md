# **클래스 명세서**

## **개요**
**1. Webserver 객체** </br>
**2. Server 객체** </br>
**[3. Server 모듈](https://github.com/wkdtpgns5016/webserve/blob/main/docs/server_module.md)** </br>
+ 3-1. ServerModule
+ 3-2. 서버 파싱 모듈
    + LocationParser
    + ServerParser
+ 3-3. 서버 컨트롤러 모듈
    + ServerController
+ 3-4. 서버 실행 모듈
    + ServerRun

**[4. Http 메세지 객체](https://github.com/wkdtpgns5016/webserve/blob/main/docs/http_message.md)** </br>
+ 4-1. Http 메세지 요소
    + StartLine
    + RequestLine
    + StatusLine
+ 4-2. Http 메세지
    + HttpMessage
    + HttpRequestMessage
    + HttpResponseMessage

**[5. 라이브러리 함수](https://github.com/wkdtpgns5016/webserve/blob/main/docs/lib_function.md)** </br>

---------------------------------------------------

## **1. WebServer 객체**
**class WebServer**
> 웹서버 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
> | list&#60;Server&#62; | _servers | private | 서버  |
**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | void run(void) | public | 웹서버 작동 메소드 |

------------------------------------------

## **2.Server 객체**
**class Server**
> 서버 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
> |  pthread_t  | _thread | private | 서버 스레드  |
> |  map&#60;string, ServerModule *&#62;  | _modules | private | 서버 모듈 컨테이너  |

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | ServerModule* selectModule(string) | public | 모듈 검색 메소드 |
> | void insertModule(string, ServerModule*) | public | 모듈 삽입 메소드 |
> | void deleteModule(string) | public | 모듈 삭제 메소드 |
> | static void run(void) | public | 서버 스레드 메소드 |
> | void threading(void) | public | 서버 스레드 시작 메소드 |

------------------------------------------
