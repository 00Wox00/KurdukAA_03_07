#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    // Если есть аргумент, это дочерний процесс: считает сумму и завершается
    if (argc > 1)
    {
        string start = "Процесс начал вычисление\n";
        cout << start;

        long long sum = 0;
        for (int i = 1; i <= 100000000; i++)
        {
            sum += i;
        }

        string result = "Сумма = " + to_string(sum) + "\n";
        cout << result;
        return 0;
    }

    // Иначе это главный процесс: запускает саму себя с аргументом child
    wchar_t lpszCmd[] = L"KurdukAA_03_07.exe child";
    STARTUPINFO si;
    PROCESS_INFORMATION pi[2];

    // Две пары процессов: сначала 1 и 2, потом 3 и 4
    for (int wave = 1; wave <= 2; wave++)
    {
        for (int j = 0; j < 2; j++)
        {
            ZeroMemory(&si, sizeof(STARTUPINFO));
            si.cb = sizeof(STARTUPINFO);

            if (!CreateProcess(NULL, lpszCmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi[j]))
            {
                cout << "Не удалось запустить процесс, код ошибки: " << GetLastError() << endl;
                return 1;
            }

            cout << "Запущен дочерний процесс " << (wave - 1) * 2 + j + 1 << endl;
        }

        // Ждём оба процесса и закрываем дескрипторы
        for (int j = 0; j < 2; j++)
        {
            WaitForSingleObject(pi[j].hProcess, INFINITE);
            CloseHandle(pi[j].hThread);
            CloseHandle(pi[j].hProcess);
        }
    }

    cout << "Все дочерние процессы завершены. Система закончила работу." << endl;

    return 0;
}