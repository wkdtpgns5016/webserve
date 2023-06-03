# **9. CGI 클래스 명세서**
**[[메인화면으로 가기]](https://github.com/wkdtpgns5016/webserve)**

## **1. CGI 객체**
**class CGI**
> CGI 객체

**Attribute**
> | 타입 | 이름 | 접근 제한 | 설명 |
> |:----------|:----------|:----------|:----------:|
> | vector&#60;Server&#62; | _servers | private | 서버  |    
> | ConfigDto | _config | private | config 객체 |
> | HttpRequestMessage | _request_message | private | 요청 메시지 객체 |
> | std::map&#60;std::string, std::string&#62; | _env | private | 환경 변수 |
**Method**
> | 함수 원형 | 접근 제한 | 설명 |
> |:----------|:----------|:----------:|
> | void initEnv(void) | private | env 초기화 메소드 |
> | void setEnv(void) | private | env 설정 메소드 |
> | char **getEnvChar(void) const | private | env char 배열 변환 메소드  |
> | std::string excute(std::string scriptName) | public | 실행 메소드 |

------------------------------------------