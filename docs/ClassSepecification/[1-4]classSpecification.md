# **클래스 명세서**
**[[메인화면으로 가기]](https://github.com/wkdtpgns5016/webserve)**

## **개요**
**1. Webserver 객체** </br>
**2. Server 객체** </br>
**3. ServerController 객체** </br>
**4. Connection 객체** </br>

**[5. RequestHandler 모듈](https://github.com/wkdtpgns5016/webserve/blob/main/docs/ClassSepecification/[5]server_handler.md)** </br>
+ 5-1. ServerHandler
+ 5-2. GetHandler
+ 5-3. PostHandler
+ 5-4. DeleteHandler
+ 5-5. PutHandler

**[6. Http 메세지 객체](https://github.com/wkdtpgns5016/webserve/blob/main/docs/ClassSepecification/[6]http_message.md)** </br>
+ 6-1. Http 메세지 요소
    + StartLine
    + RequestLine
    + StatusLine
+ 6-2. Http 메세지
    + HttpMessage
    + HttpRequestMessage
    + HttpResponseMessage
 + 6-3. RequestMessageParser
 
**[7. Configuration 모듈](https://github.com/wkdtpgns5016/webserve/blob/main/docs/ClassSepecification/[7]configuration.md)** </br>
+ 7-1. Block 객체
    + Block
    + ServerBlock
    + LocationBlock
+ 7-2. conf 객체
    + Conf
    + ConfDto
+ 7-3. 파싱 모듈
    + Parser
    + Scripter

**[8. 라이브러리 함수](https://github.com/wkdtpgns5016/webserve/blob/main/docs/ClassSepecification/[8]lib_function.md)** </br>

---------------------------------------------------

## **1. WebServer 객체**
**class WebServer**
> 웹서버 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
> | vector&#60;Server&#62; | _servers | private | 서버  |
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
> |  pthread_t  | _s_thread | private | 서버 스레드  |
> |  int        | _server_socket | private | 서버 소켓  |
> |  int        | _kqueue | private | 이벤트 큐 |
> |  struct sockaddr_in | _server_addr | private | 서버 주소  |
> |  struct kevent* | _curr_event | private | 이벤트 구조체 |
> |  struct kevent | _event_list[8] | private | 이벤트 리스트 |
> |  vector&#60;struct kevent&#62; | _change_list | private | 이벤트 리스트  |
> |  map&#60;int, Connection&#62; |  _clients | private | 클라이언트 맵  |
> |  ServerBlock* | _server_block | private | 서버 설정 블럭 |

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | void socket_init(int port, unsigned int ip_addr) | private | 소켓 초기화 함수 |
> | void change_events(uintptr_t ident, int16_t filter, uint16_t flags, uint32_t fflags, intptr_t data, void *udata) | private | 이벤트 리스트 등록 함수 |
> | void disconnect_client(int client_fd, std::map&#60;int, Connection&#62; &clients) | private | 클라이언트 삭제 함수 |
> | void accept_new_client()| private | 신규 클라이언트 등록 함수 |
> | void receiveMessage() | private | 메세지 수신 함수 |
> | void sendMessage() | private | 메세지 송신 함수 |
> | static void* threadFunction(void *) | private | 스레드 함수 |
> | pthread_t getThread(void) | public | 스레드 getter
> | int  getPort(void) | public | port getter
> | void run() | public | 서버 시작 함수
> | void threading(void) | public | 스레드 시작 함수
------------------------------------------

## **3. ServerController 객체**
**class ServerController**
> 서버 컨트롤러 객체 - 각 요청 메소드에 따라서 ServerHandler를 실행

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> |LocationBlock* findLocationBlock(std::vector&#60;Block*&#62; locations, std::string request_target) | private | request target에 대한 location 블럭 반환 함수 |
> |HttpResponseMessage requestHandler(ServerBlock* server_block, HttpRequestMessage request_message) | public | 요청 메세지에 대한 request handler |

------------------------------------------

## **4. Connection 객체**
**class Connection**
> 서버와 클라이언트의 메시지 송수신을 담당하는 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
> | int         | private | _client_fd | 클라이언트 소켓 fd |
> | std::string | private | _client_addr | 클라이언트 주소 |
> | RequestMessageParser | private | _message_parser | Http 요청 메시지 파서 |

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | bool checkMessage() | private | 메시지 완성 검사 함수 |
> | void receiveMessage() | public | 메시지 수신 함수 |
> | bool sendMessage(ServerBlock *Server_block) | public | 메시지 송신 함수 |
> | std::string getClinetAddr() const | public | 클라이언트 주소 getter |