## Відкриття у Visual Studio

Відкрийте `lab09.sln` у Microsoft Visual Studio з компонентом **Розробка класичних програм мовою C++**. Вихідний `main.cpp` має лежати поруч із `.sln` та `.vcxproj`; додаткові бібліотеки не потрібні. Проєкт налаштовано на MSVC, C++14, `/EHsc`, платформу **x64**, Windows SDK 10.0 та набір інструментів **v143**.

Оберіть **Debug | x64** або **Release | x64**, виконайте **Build Solution**, потім запустіть **Ctrl+F5**, щоб переглянути весь консольний результат. Програма не потребує введення. Виконуваний файл з’явиться в `bin\x64\Debug\lab09.exe` або `bin\x64\Release\lab09.exe`.

У Developer Command Prompt for Visual Studio можна зібрати й запустити так:

```bat
msbuild lab09.sln /m /p:Configuration=Debug /p:Platform=x64
bin\x64\Debug\lab09.exe
```

Якщо встановлено інший сумісний MSVC toolset, його можна явно вибрати параметром `/p:PlatformToolset=...`. Це змінює інструмент складання, але не стандарт C++14 або вихідний код.
