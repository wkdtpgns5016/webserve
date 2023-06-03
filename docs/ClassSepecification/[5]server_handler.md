## **5. RequestHandler 모듈**
**[[메인화면으로 가기]](https://github.com/wkdtpgns5016/webserve)**
> **서버 핸들러 개요**
> + 5-1. ServerHandler
> + 5-2. GetHandler
> + 5-3. PostHandler
> + 5-4. DeleteHandler
> + 5-5. PutHandler

## **5-1. ServerHandler 객체**
**class ServerHandler**
> 요청 핸들러 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
> | vector&#60;Server&#62; | _servers | private | 서버  |
> | std::map&#60;int, std::string&#62; | _status | private | status code 자료 구조체 |
> | HttpRequestMessage | _request_message | private | 요청 메세지 |
> | ConfigDto | _config | private | 설정 객체 |

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | void init_status() | private | status 초기화 함수 |
> | LocationBlock* findLocationBlock(std::vector&#60;Block*&#62;locations, std::string request_target) | private | request target에 대한 location 블럭 반환 함수 |
> | std::string cleanUrl(std::string url, boolrequest_target) | private | url 변경 함수 |
> | void checkAllowMethod(std::string method) | private | 메서드 허용 검사 |
> | void checkHttpVersion(RequestLine start_line) | private | 버전 검사 |
> | void checkMessageSize(void) | private | http 메세지 크기 검사 |
> | void checkHttpMessage(void) | private | http 메세지 검사 |
> | bool checkDirectory(std::string path) | private | 디렉토리 검사 |
> | bool checkFile(std::string request_target) | private | 파일 검사 |
> | std::vector&#60;std::string&#62; getIndexPath(std::string root, std::string index) | private | index path 반환 함수 |
> | std::string tryFiles(std::vector&#60;std::string&#62; try_files) | private | try files 처리 함수 |
> | std::string findPath(std::string request_target) | private | path 찾는 함수 |
> | std::string executeCgi(std::string request_target) | private | cgi 실행 함수 |
> | std::map&#60;std::string, std::string&#62; getCgiHeader(std::vector&#60;std::string&#62; arr) | private | cgi header 추가 메소드 |
> | int getStautsCgi(std::map&#60;std::string, std::string&#62; cgi_header) | private | cgi 결과 status 설정 메소드 |
> | std::map&#60;std::string, std::string&#62; setHeader(int status_code,  std::string message_body) | private | header setter |
> | void throwStatusError(int status_code) | private | error 예외 throw 메소드 |
> | HttpResponseMessage getErrorResponse(int status_code) | private | error 응답 메세지 반환 함수 |
> | HttpResponseMessage getResponseMessage(int status_code, std::string message_body) | private | 응답 메세지 반환 함수 |
> | HttpRequestMessage& getRequestMessage(void) | public | 요청 메세지 getter |
> | virtual HttpResponseMessage requestHandler() = 0 | public | 리퀘스트 핸들러 순수 가상 함수 |
------------------------------------------

## **5-2. GetHandler 객체**
**class GetHandler**
> GET 핸들러 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | std::string openFile(std::string reqeuest_target) | private | file 내용 반환 함수 |
> | std::string getAutoIndexPage(std::string path std::string request_target) | private | autoindex 페이지 반환 |
> | std::string getDirectoryList(std::string path) | private | 디렉토리 리스트 반환 함수 |
> | HttpResponseMessage requestHandler() | public | 요청 핸들러 함수 |

------------------------------------------

## **5-3. PostHandler 객체**
**class PostHandler**
> POST 핸들러 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | void checkCGI(std::string path) | private | CGI 파일 체크 함수 |
> | HttpResponseMessage requestHandler() | public | 요청 핸들러 함수 |
------------------------------------------

## **5-4. PutHandler 객체**
**class PutHandler**
> PUT 핸들러 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | int openFile(std::string path) | private | file open 함수 |
> | void writeFile(int fd, std::string message) | private | 파일 내용 write 함수 |
> | int putMethod() | private | PUT 메서드 핸들러 함수 |
> | HttpResponseMessage requestHandler() | public | 요청 핸들러 함수 |
------------------------------------------

## **5-5. DeleteHandler 객체**
**class DeleteHandler**
> DELETE 핸들러 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | void deleteFile(std::string request_target) | private | 파일 삭제 함수 |
> | HttpResponseMessage requestHandler() | public | 요청 핸들러 함수 |
------------------------------------------