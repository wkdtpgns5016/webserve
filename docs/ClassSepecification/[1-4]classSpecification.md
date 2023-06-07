# **클래스 명세서**
**[[메인화면으로 가기]](https://github.com/wkdtpgns5016/webserve)**

## **개요**
**1. Webserver 객체** </br>
**2. Server 객체** </br>
**3. ServerController 객체** </br>
**4. Connection 객체** </br>
**4-2. Buffer 객체** </br>

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

**[8. Log 모듈](https://github.com/wkdtpgns5016/webserve/blob/main/docs/ClassSepecification/[8]log_module.md)** </br>
+ 8-1. Logger 객체
+ 8-2. CommonLogFormat 객체

**[9. CGI 객체](https://github.com/wkdtpgns5016/webserve/blob/main/docs/ClassSepecification/[9]cgi.md)** </br>

**[10. 라이브러리 함수](https://github.com/wkdtpgns5016/webserve/blob/main/docs/ClassSepecification/[10]lib_function.md)** </br>

---------------------------------------------------

## **1. WebServer 객체**
**class WebServer**
> 웹서버 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
> | map&#60;int, Server*&#62; | _servers | private | 서버 맵1 |
> | map&#60;int, Server*&#62; | _servers_with_clients | private | 서버 맵2 |
**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | int	initSocket(int port, unsigned int ip_addr) | private | 소켓 생성 메소드 |
> | void change_events(uintptr_t ident, int16_t filter, uint16_t flags, vector&#60;struct kevent&#62; * change_list) | private | 이벤트 체인지 메소드 |
> | void accept_new_client(vector&#60;struct kevent&#62;*  change_list, int server_socket) | private | 클라이언트 등록 함수 |
> | void run(void) | public | 웹서버 작동 메소드 |

------------------------------------------

## **2.Server 객체**
**class Server**
> 서버 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
> |  int        | _server_fd | private | 서버 소켓  |
> |  vector&#60;ServerBlock *&#62; | _configs_ | private | 설정 벡터  |
> |  map&#60;int, Connection&#62; |  _clients | private | 클라이언트 맵  |

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | void disconnect_client(int client_fd) | public | 클라이언트 연결 끊는 함수 |
> | void accept_new_client(int client_fd, const string& addr) | public | 클라이언트 연결 함수 |
> | void checkConnectionTimeout() | public | 커넥션 타임아웃 체크 함수 |
> | void sendMessage(int client_fd) | public | 메시지 전송 함수 |
> | void recvMessage(int client_fd) | public | 메시지 수신 함수 |
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
> |time_t | private | _current_connection_time | 최근 연결 시각 |
> | RequestMessageParser | private | _message_parser | Http 요청 메시지 파서 |
> | HttpRequestMessage | private | _request | 요청 객체 |
> | HttpResponseMessage | private | _response | 응답 객체 |
> | Buffer      | private | _buffer | 전송 버퍼 |
> | bool        | private | _complete_respose | 응답 완성 플래그 |

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | bool checkMessage() | private | 메시지 완성 검사 함수 |
> | bool checkResponse() | private | 응답 완성 확인 메소드 |
> | void makeResponse(ServerBlock *server_block) | private | 응답 생성 메소드 |
> | void updateConnectionTime() | private | 최근 연결 시각 초기화 |
> | void receiveMessage() | public | 메시지 수신 함수 |
> | bool sendMessage(ServerBlock *Server_block) | public | 메시지 송신 함수 |
> | std::string getClinetAddr() const | public | 클라이언트 주소 getter |
> | void clearConnection() | public | 커넥션 초기화 메소드 |
> | int getClinetFd() const | public | 클라이언트 fd 반환 메소드 |
> | time_t getCurrentConnectionTime() const | public | 최근 연결 시각 반환 메소드 |

------------------------------------------

## **4-2. Buffer 객체**
**class Buffer**
> 클라이언트 송신 버퍼 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
> | string | _buffer | private | 버퍼 |
> | size_t | _pos | private | 버퍼 인덱스 |

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | void appendBuffer(const string& str) | public | 버퍼 메시지 추가 함수 |
> | void cutBuffer(size_t pos) | public | 버퍼 내용 자르기 함수 |
> | void clearBuffer(void) | public | 버퍼 비우기 함수 |
> | const char* getBuffer(void) const | public | 버퍼 getter |