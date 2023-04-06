# **클래스 명세서**

## **WebServer**
> 웹서버 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
> | list&#60;Server&#62; | _servers | private | 서버  |
> | Reader | _reader | private | 파일 리더기  |

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|

------------------------------------------

## **Server**
> 실제 구동하는 서버 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
> |  ServerParser  | _server_config | private | 서버 설정 객체  |

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | void run() | public | 서버 작동 메서드 |

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
> | list< LocationParser > | _locations | private | location block 리스트 |

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | void serverBlockParsing(string) | public | 문자열을 인자로 받아 객체를 파싱하는 함수 |

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
> | list<string> | _allow_method | private | 허용 http 메소드 목록 |

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | void locationBlockParsing(string) | public | 문자열을 인자로 받아 객체를 파싱하는 함수 |


## **Reader**
> 파일 리더기

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
> | int | _fd | private | 파일 디스크럽터  |

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | vector&#60;string&#62; splitString(string, string) | public | 문자열을 특정 문자열 기준으로 자르는 함수 |
> | vector&#60;string&#62; splitBlockWithString(string) | public | Block을 기준으로 문자열을 자르는 함수  |
> | stirng readFile(string) | public | 파일 경로를 인자로 받아 파일 내용을 문자열로 반환하는 함수 |