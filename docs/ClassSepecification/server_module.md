## **3. Server 모듈**
> **서버 모듈 개요**
> + 3-1. ServerModule
> + 3-2. 서버 파싱 모듈
>     + LocationParser
>     + ServerParser
> + 3-3. 서버 컨트롤러 모듈
>     + ServerController
> + 3-4. 서버 실행 모듈
>     + ServerRun

### **3-1. 서버 모듈**
**class ServerModule**
> 서버 모듈 부모 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
> | Server * | _self | protected | 서버 객체를 가리키는 포인터 변수 |

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|

------------------------------------------
### **3-2. 서버 파싱 모듈**

**class LocationParser**
> 설정파일 내의 loaction block 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
> | string | _url | private | url |
> | string | _root | private | 기본적으로 파일을 검색하는 경로 |
> | string | _index | private | 파일 명시 안되었을 경우 리다이렉션 하는 파일 경로 |
> | string | _upload_path | private | 파일 업로드 위치 |
> | bool | _auto_index | private | autoindex 설정 여부 |
> | list&#60;string&#62; | _allow_method | private | 허용 http 메소드 목록 |

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | string getUrl(void) const | public | url getter |
> | string getRoot(void) const | public | root getter |
> | string getIndex(void) const | public | index getter |
> | string getUploadPath(void) const | public | upload_path getter |
> | bool getAutoIndex(void) const | public | auto_index getter |
> | list&#60;string&#62; getAllowMethod(void) const | public | allow_method getter |
> | void locationBlockParsing(string) | public | 문자열을 인자로 받아 객체를 파싱하는 함수 |

-------------------------------------------
**class ServerParser**
> 설정파일 내의 server block 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
> | int | _port | private | 포트 번호 |
> | string | _addr | private | 서버 주소 |
> | string | _server_name | private | 서버 이름 |
> | string | _index | private | 파일 명시 안되었을 경우 리다이렉션 하는 파일 경로 |
> | string | _default_error_page | private | 기본 에러 페이지 위치 |
> | int | _client_body_size | private | 클라이언트 바디 길이 제한 |
> | list&#60;LocationParser&#62; | _locations | private | location block 리스트 |

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | int getPort(void) const | public | port getter |
> | string getAddr(void) const | public | addr getter |
> | string getServerName(void) const | public | server_name getter |
> | string getIndex(void) const | public | index getter |
> | string getDefaultErrorPage(void) const | public | default_error_page getter |
> | string getClinetBodySize(void) const | public | client_body_size getter |
> | list&#60;LocationParser&#62; getLocations(void) const | public | locations getter |
> | void parseServerBlock(string) | private | serverblock parsing |
> | void parsePort(string) | private | port parsing |
> | void parseAddr(string) | private | server address parsing |
> | void parseServerName(string) | private | server name parsing |
> | void parseIndex(string) | private | index parsing |
> | void parseDefaultErroPage(string) | private | errorpage parsing |
> | void parseClientBodySize(string) | private | client body size parsing |
> | void passLocationBlock(string) | private | pass location block to LocationParser |

------------------------------------------
### **3-3. 서버 컨트롤러 모듈**

**3-3. ServerController**
> 서버 컨트롤러 모듈

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
> | HttpRequestMessage | _request_message | private | http 요청 메세지 |

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | HttpResponseMessage getHandler(void) | private | GET 메소드 핸들러 |
> | HttpResponseMessage postHandler(void) | private | POST 메소드 핸들러 |
> | HttpResponseMessage deleteHandler(void) | private | DELETE 메소드 핸들러 |
> | HttpResponseMessage requestHandler(void) | public | Http 요청 메세지 핸들러 |
> | HttpRequestMessage HttpRequestMessage(void) | public | 요청 메세지 getter |
> | void setRequestMessage(string) | public | Http 요청 메세지 setter |

------------------------------------------
### **3-4. 서버 실행 모듈**

**3-3. ServerRun**
> 서버 실행 모듈

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | void run(void) | public | 서버 작동 메서드 |

------------------------------------------