# **8. 라이브러리 함수**
**[[메인화면으로 가기]](https://github.com/wkdtpgns5016/webserve)**
> webserce 과제에서 필요한 범용적인 함수들을 모아 ft 네임스페이스에 별도 구현

### **필요 함수**
> | 함수 원형 | 설명 |
> |:----------|:----------:|
> | string readFileIntoString(string) | 파일 안에 있는 문자열 반환 |
> | vector&#60;string&#62; splitString(string, string) | 문자열을 특정 문자열 기준으로 자르는 함수 |
> | vector&#60;string&#62; splitBlockWithString(string) | Block을 기준으로 문자열을 자르는 함수  |
> | std::vectorr&#60;std::stringr&#62; getTime(time_t timer) | 현재 시간 출력 함수 |
> | std::string itos(int num) | convert int to string |
> | int stoi(std::string str) | convert string to int |
> | size_t stoul(std::string str) | convert string to size_t |
> | unsigned int convertHex(std::string hex) | convert hex to unsigned int |