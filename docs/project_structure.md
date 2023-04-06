# **프로젝트 구조**

### **Canonical Project Structure**
>https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1204r0.html
### **webserve 프로젝트 구조**
    webserve/       # 프로젝트 루트
    ├── webserve/       # 소스 파일 디렉토리
    │   ├── Reader/           # 객체1
    │   │   ├── Reader.cpp        # 객체1 소스 코드
    │   │   ├── Reader.hpp        # 객체1 헤더
    │   │   └── Reader.test.cpp   # 객체1 단위 테스트 코드
    │   └── 객체_2/           # 객체2
    │       ├── 객체_2.cpp        # 객체2 소스 코드
    │       ├── 객체_2.hpp        # 객체2 헤더
    │       └── 객체_2.test.cpp   # 객체2 단위 테스트 코드
    ├── docs/           # 프로젝트 문서
    ├── docs/           # 프로젝트 문서
    ├── tests/          # 기능/통합 테스트
    └── CMakeList.txt   # cmake 파일
객체에 대한 디렉토리 구조는 객체의 성격에 따라 다시 재분류 및 재구조화 될 수 있음