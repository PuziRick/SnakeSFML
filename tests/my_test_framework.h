#pragma once 

#include <cassert>
#include <iostream>
#include <string>

using std::literals::string_literals::operator""s;

/*  Пример использования
    1) ASSERT_EQUAL(a,b)
    {
        int result = 1;
        int task_result = 2;
        ASSERT_EQUAL(result, task_result); 
        // OUTPUT: "file_name: func_name: ASSERT_EQUAL(result, task_result) failed: 1 != 2."
    }

    2) ASSERT_EQUAL_HINT(a,b,hint)
    {
        int result = 1;
        int task_result = 2;
        ASSERT_EQUAL_HINT(result, task_result, "Realy?");
        // OUTPUT: "file_name: func_name: ASSERT_EQUAL(result, task_result) failed: 1 != 2. Hint: Realy?")
    }

    3) ASSERT(expr)
    {
        auto isZero = [](int num) {
            return num == 0;
        };
        ASSERT(isZero(2)); 
        // OUTPUT: "file_name: ASSERT(isZero(2)) failed."
    }

    4) ASSERT_HINT(expr, hint)
    {
        auto isZero = [](int num) {
            return num == 0;
        };
        ASSERT(isZero(2), "Realy?"); 
        // OUTPUT: "file_name: ASSERT(isZero(2)) failed. Hint: Realy?"
    }

    5) RUN_TEST(func)
    {
        auto AVeryThoughtfulIncrediblyProfessionalTestThatTakesEverythingIntoAccount = []() {
            return 0;
        };
        RUN_TEST(AVeryThoughtfulIncrediblyProfessionalTestThatTakesEverythingIntoAccount());
        // OUTPUT: "AVeryThoughtfulIncrediblyProfessionalTestThatTakesEverythingIntoAccount OK"
    }
*/

// Сравнение двух величин (полученную в результате работы и правильной (по мнению автора))
// использовать через макрос
template <typename T, typename U>
void AssertEqualImpl(const T& t, const U& u, const std::string& t_str, const std::string& u_str, const std::string& file,
                     const std::string& func, unsigned line, const std::string& hint) {
    if (static_cast<T>(t) != static_cast<T>(u)) {
        std::cerr << std::boolalpha;
        std::cerr << file << "("s << line << "): "s << func << ": "s;
        std::cerr << "ASSERT_EQUAL("s << t_str << ", "s << u_str << ") failed: "s;
        std::cerr << t << " != "s << u << "."s;
        if (!hint.empty()) {
            std::cerr << " Hint: "s << hint;
        }
        std::cerr << std::endl;
        std::abort();
    }
}

// Макрос сравнивает две величины, если выпадает ошибка пишет где она произошла
#define ASSERT_EQUAL(a, b) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, ""s)

// Тоже что и ASSERT_EQUAL, но можно указать причину ошибки
#define ASSERT_EQUAL_HINT(a, b, hint) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, (hint))

// Работает аналогично assert, только выдает дополнительную информацию
// использовать через макрос
void AssertImpl(bool value, const std::string& expr_str, const std::string& file, const std::string& func, unsigned line,
                const std::string& hint) {
    if (!value) {
        std::cerr << file << "("s << line << "): "s << func << ": "s;
        std::cerr << "ASSERT("s << expr_str << ") failed."s;
        if (!hint.empty()) {
            std::cerr << " Hint: "s << hint;
        }
        std::cerr << std::endl;
        abort();
    }
}

// Работает как обычный assert, только дает больше информации
#define ASSERT(expr) AssertImpl(!!(expr), #expr, __FILE__, __FUNCTION__, __LINE__, ""s)

// Аналог ASSERT(expr), но можно указать причину ошибки
#define ASSERT_HINT(expr, hint) AssertImpl(!!(expr), #expr, __FILE__, __FUNCTION__, __LINE__, (hint))

// Для удобной работы с тестами (передает функцию, получаем изящную надпись)
// запускать через макрос
template <typename Function>
void RunTestImpl(Function func, const std::string& func_name, int num_of_tab = 0) {
    func();
    for (int i = 0; i < num_of_tab; ++i) {
        std::cerr << "  ";
    }
    std::cerr << func_name << " OK" << std::endl;
}

// Делает магию
#define RUN_TEST(func) RunTestImpl((func), (#func))
#define RUN_TEST_TAB(func, tab) RunTestImpl((func), (#func), tab)