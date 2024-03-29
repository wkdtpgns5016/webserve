# **테스트 주도 개발 프로그래밍**
**[[메인화면으로 가기]](https://github.com/wkdtpgns5016/webserve)**
> 웹서브 테스트 주도 개발 프로그래밍 </br>
> 출처 : https://mangkyu.tistory.com/182#recentComments

### **좋은 테스트 코드 특징 (FIRST)**
    1. Fast: 테스트는 빠르게 동작하여 자주 돌릴 수 있어야 한다.
    2. Independent: 각각의 테스트는 독립적이며 서로 의존해서는 안된다.
    3. Repeatable: 어느 환경에서도 반복 가능해야 한다.
    4. Self-Validating: 테스트는 성공 또는 실패로 bool 값으로 결과를 내어 자체적으로 검증되어야 한다.
    5. Timely: 테스트는 적시에 즉, 테스트하려는 실제 코드를 구현하기 직전에 구현해야 한다.
좋은 테스트는 <U>빠르게 독립적으로 어느 환경에서든 실행이 가능하고 검증</U>할 수 있어야 한다는 것이다. 만약 테스트를 실행하는 비용이 크다면 그럴 바에는 통합테스트를 하는게 더 나을 수도 있다.</br> 그리고 우리는 위의 5가지 규칙 중에서 Timely에 주목해야 할 필요가 있다. 테스트 코드를 작성하는 시점에 대한 이야기인데, CleanCode에서는 <U>테스트 코드를 실제 코드를 구현하기 직전에 구현</U>하라고 설명하고 있다. 즉, 테스트 코드를 먼저 작성하라는 것이다. 우리는 왜 테스트 코드를 먼저 작성해야 하고, 어떻게 테스트 코드를 먼저 작성할 수 있는지에 대해 알아야 한다.

### **테스트 코드를 먼저 작성해야 하는 이유**
    1. 깔끔한 코드를 작성할 수 있다.
    2. 장기적으로 개발 비용을 절감할 수 있다.
    3. 개발이 끝나면 테스트 코드를 작성하는 것은 매우 귀찮다. 실패 케이스면 더욱 그렇다.

### **TDD(test-driven development)**
> 테스트 주도 개발(test-driven development, TDD)은 소프트웨어 개발 방법론 중의 하나로, 선 개발 후 테스트 방식이 아닌 선 테스트 후 개발 방식의 프로그래밍 방법을 말한다. 다시 말해 먼저 자동화된 테스트 코드를 작성한 후 테스트를 통과하기 위한 코드를 개발하는 방식의 개발 방식을 말한다.

### **TDD를 이용한 개발 프로세스**
    1. 테스트 케이스 작성
    2. 테스트 케이스를 통과하는 코드 작성
    3. 코드 리팩토링
    4. 1번 부터 반복
먼저 테스트 케이스와 테스트 코드를 작성한다. 테스트 코드가 개발을 주도하기 위해서는 <U>반드시 실패를 포함하는 테스트 코드의 작성이 앞서야 한다.</U> 다음으로는 테스트 케이스를 통과하는 코드를 작성한다. 작성된 코드는 개선될 수 있는 많은 여지를 포함한 코드이다. 마지막으로 리팩토링 단계에서 이를 개선한다.

### **TDD 접근 방법**
    1. 빨간 막대, 초록 막대
    2. given / when / then 패턴
    3. 가짜로 구현하기
    4. 삼각 측량법
    5. 명확하게 구현하기
    6. Mock 활용

- **빨간 막대, 초록 막대**
    > **빨간 막대** : 실패하는 작은 테스트를 작성 </br>
    **초록 막대** : 코드가 테스트를 통과하도록 신속하게 작동하는 코드 작성. 빨리 테스트가 작동하여, 통과하도록 함.


- **given / when / then 패턴**
    > **Given** : 테스트에 사용되는 변수, 입력 값을 정의하거나 Mock 객체를 정의하는 구문 포함</br>
    **When** : 실제로 액션을 하는 테스트 </br>
    **Then** : 테스트를 검증. 예상한 값과 실제 실행을 통해 나온 값을 검증한다. </br>
    ```c++
    /** 
    * test code
    * sum(a, b) 이라는 기능을 테스트
    */
    void sumUnitTest()
    {
        // given : 준비
        int a = 3;
        int b = 3;

        // when : 실행
        int result = sum(a, b);

        // then : 검증
        assertThat(result).isEqualTo(6);
    }

    ```
- **가짜로 구현하기**
    > 위의 테스트를 가장 빠르게 통과하는 방법은 6을 반환하는 것이다.
     ```c++
    /** 
    * test code
    * sum(a, b) 이라는 기능을 테스트
    */
    int sum(int a, int b)
    {
        return (6);
    }

    ```
    이렇게 변수를 사용하지 않고 상수를 반환하며, 답이 아닌 방법으로 가짜 구현하여 최대한 빨리 테스트를 통과하는 것이 가짜 구현 방법이다. 가짜 구현으로 개발하면 다음과 같은 2가지 효과를 얻을 수 있다. </br>
    >**심리학적**: 빨간 막대와 초록 막대 상태는 완전히 다르다. 막대가 초록색이라면 어느 위치인지 알고 거기부터 리팩토링해 갈 수 있다. </br>
    **범위 조절**: 하나의 구체적인 예에서 일반화를 함으로써, 불필요한 고민으로 혼동되는 일을 예방할 수 있다.

- **삼각 측량법**
    > 삼각 측량은 테스트 주도로 추상화된 과정을 일반화하는 과정이다. 삼각 측량 방법은 테스트 예시가 2개 이상일 때에만 추상화를 해야 한다. 

    ```c++
    /** 
    * test code
    * sum(a, b) 이라는 기능을 테스트
    */
    void sumUnitTest()
    {
        // given : 준비

        // when : 실행
        int result1 = sum(1, 3);
        int result2 = sum(4, 7);

        // then : 검증
        assertThat(result1).isEqualTo(4);
        assertThat(result2).isEqualTo(11);
    }

    ```

- **명확하게 구현하기**
    > 명백하게 구현하는 방법은 가짜 구현이나 삼각 측량 방법을 사용하지 않고 바로 정답을 구현하는 방법이다. </br>
    현재 사용하는 더하기와 같은 문제는 쉬우므로 다음과 같이 바로 진짜 구현을 해도 괜찮다.

    ```c++
    /** 
    * test code
    * sum(a, b) 이라는 기능을 테스트
    */
    int sum(int a, int b)
    {
        return (a + b);
    }

    ```

- **Mock 활용**
    > https://heegs.tistory.com/16 </br>
    > 실제 객체를 다양한 조건으로 인해 제대로 구현하기 어려울 경우 가짜로 만들어 사용하는데, 이를 Mock 이라 한다

    **Mcok 개념 분류**
    > | 유형 종류 |  |
    > |:----------|:----------:|
    > | **테스트더블** | - 테스트를 진행하기 어려운 경우 대신해 테스트를 진행할 수 있도록 만들어주는 객체 <br> - Mock객체와 유사한 의미, 테스트 더블이 좀더 상위 의미로 사용. |
    > | **더미객체(Dommy Object)** | - 단순히 인스턴스화될 수 있는 수준으로만 객체를 구현 <br> - 객체가 필요할 뿐 객체의 기능까지는 필요하지 않은 경우에 사용. |
    > | **테스트스텁(Test Stub)** | - 더미 객체가 실제로 동작하는 것처럼 보이게 만들어놓은 객체 <br> - 특정 값을 리턴해 주거나 특정 메시지를 출력해주는 작업 <br> - 특정 상태를 가정하여 하드코딩된 형태이기 때문에, 로직에 따른 값의 변경을 테스트 할 수 없다. |
    > | **페이크객체(Fake Object)** | - 여러 상태를 대표할 수 있도록 구현된 객체로, 실제 로직이 구현된 것 처럼 보이게 한다 </br> - 실 DB에 접속해 동일한 모양이 보이도록 객체 내부에 구현할 수 있다. |
    > | **테스트스파이(Test Spy)** | - 테스트 더블로 구현된 객체에 자기 자신이 호출 되었을 떄 확인이 필요한 부분을 기록하도록 구현 </br> - 행위 기반 테스트가 필요한 경우 사용. |
    > | **Mock 객체** | 행위를 검증하기 위해 사용되는 객체를 지칭 </br> - 수동으로 만들 수도 있고 프레임 워크를 사용해 만들 수 있다 |

    > Mock 객체는 **행위 검증**에 사용하고, Stub은 **상태 검증**에 사용한다.


### **Google Test 사용**
**1. cmake 설치**
```
brew install cmake
```

**2. Google Test 환경 구성** </br>
> 1. github에 있는 Google Test 릴리즈 버전을 선택하여 내려 받는다 </br>
> (https://github.com/google/googletest/releases) </br>
> 2. 프로젝트 내 test 디렉토리에 붙여 넣는다
> 3. 테스트 코드 작성
> 4. CMakeList.txt 작성
> 테스트 실행

**3. CMakeList.txt 작성**
```
# cmake 버전
cmake_minimum_required(VERSION 3.24)
# 프로젝트 이름
project(webserve-test)

# c++ 지원 버전
set(CMAKE_CXX_STANDARD 17)

# 라이브러리 빌드 (C 코드)
add_library(sum SHARED lib/sum.c lib/sum.h)

# 실행 프로그램 빌드 (C 코드)
include_directories(lib)
add_executable(webserve-test main.cpp)
target_link_libraries(webserve-test sum)

# gtest 빌드 (C++ 코드)
set(gtest_SRC_DIR test/googletest-1.13.0)
add_subdirectory(${gtest_SRC_DIR})

# 테스트 프로그램 빌드 (C++ 코드)
include_directories(lib)
include_directories(${gtest_SRC_DIR}/googletest/include)
add_executable(테스트실행파일명 test/sum_test.cc)
target_link_libraries(테스트실행파일명 gtest gtest_main)
target_link_libraries(테스트실행파일명 sum)
```

**4. 테스트 실행**
```
cmake -S . -B build 
cmake --build build
cd build
./테스트실행파일명
```