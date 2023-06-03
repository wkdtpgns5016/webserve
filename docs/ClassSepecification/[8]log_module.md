# **8. Log Module 클래스 명세서**
**[[메인화면으로 가기]](https://github.com/wkdtpgns5016/webserve)**

## **8-1. Logger 객체**
**class Logger**
> Logger static class

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | static void writeLog(std::string client_ip, HttpRequestMessage request, HttpResponseMessage response, int write_fd) | public | CommonLogFormat 로그 출력 메소드 |
> | static void writeLog(std::string addr, int socket_fd, std::string messsage, int write_fd) | public | 일반 로그 메시지 출력 메소드 |

------------------------------------------

## **8-2. CommonLogFormat 객체**
**class CommonLogFormat**
> CommonLogFormat class

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
> | std::string _remote_host | private | host addr |
> | std::string _user_name | private | user name |
> | std::string _auth_user_name | private | auth user name |
> | std::string _time_stamp | private | time |
> | RequestLine _request_line | private | start line |
> | int         _status_code | private | status code  |
> | std::string _response_size | private | 응답 크기 |

**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | void initTimeStamp(void) | private | 타임 스탬프 초기화 |
> | std::string getString(void) | private | 로그 문자열 반환 함수 |
> | void wirteLogMessage(int fd) | private | 로그 출력 함수 |
> | std::string getRemoteHost(void) const | public | host addr getter |
> | std::string getUserName(void) const | public | user name getter |
> | std::string getAuthUserName(void) const | public | auth name getter |
> | std::string getTimeStamp(void) const | public | time stamp getter |
> | RequestLine getRequestLine(void) const | public | start line getter |
> | int getStatusCode(void) const | private | public | status getter |
> | std::string getResponseSize(void) const | public | 응답 크기 getter |

------------------------------------------