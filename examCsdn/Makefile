CC := g++  
TARGET := threadpool  
INCLUDE := -I./  
LIBS := -lpthread   
      
# C++语言编译参数  
CXXFLAGS := -g -Wall -D_REENTRANT   
      
# C预处理参数  
# CPPFLAGS :=   
      
OBJECTS := test.o Thread.o   
      
$(TARGET): $(OBJECTS)   
$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)   
      
# $@表示所有目标集  
%.o:%.cpp   
$(CC) -c $(CXXFLAGS) $(INCLUDE) $< -o $@   
      
.PHONY : clean  
clean:   
-rm -f $(OBJECTS) $(TARGET)  
