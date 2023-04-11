# **클래스 명세서**

## **WebServer**
> 웹서버 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
> | list&#60;Server&#62; | _servers | private | 서버  |
**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|

------------------------------------------

## **Server**
> 서버 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
> |  ServerParser  | _config_module | private | 서버 설정 객체  |
> |  ServerRun  | _run_moudle | private | 서버 구동 객체  |

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | void run(void) | public | 서버 작동 메서드 |

------------------------------------------

## **ServerRun**
> 실제 구동하는 서버 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | void run(void) | public | 서버 작동 메서드 |

------------------------------------------

## **ServerParser**
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

## **LocationParser**
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

------------------------------------------------

## **StartLine**
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

## **RequestLine**
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

## **StatusLine**
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

## **HttpMessage**
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

## **HttpRequestMessage**
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

## **HttpResponseMessage**
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

## **[라이브러리 목록](https://github.com/wkdtpgns5016/webserve/blob/main/docs/lib_function.md)** </br>
