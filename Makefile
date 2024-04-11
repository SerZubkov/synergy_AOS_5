# Определение компилятора
CXX=g++

# Опции компиляции
CXXFLAGS=-Wall -pthread -std=c++11

# Имя исполняемого файла
TARGET=matrix_multiply

# Исходный файл
SRC=matrix_multiply.cpp

# Объектный файл
OBJ=$(SRC:.cpp=.o)

# Правило по умолчанию
all: $(TARGET)

# Как собрать цель
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Как собрать объектные файлы
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Правило для очистки проекта
clean:
	rm -f $(TARGET) $(OBJ)

# Правило для запуска программы
run: $(TARGET)
	./$(TARGET)

# Отключение встроенных правил
MAKEFLAGS += --no-builtin-rules
.SUFFIXES:
