test:
	g++ -o main ../../7.c -g -fsanitize=address
	./main>out.txt test1.txt && diff out.txt result1.txt
	./main>out.txt test2.txt && diff out.txt result2.txt
	./main>out.txt test3.txt && diff out.txt result3.txt
	./main>out.txt test10.txt && diff out.txt result10.txt
	./main>out.txt test9.txt && diff out.txt result9.txt
	./main>out.txt test7.txt && diff out.txt result7.txt
	./main>out.txt test6.txt && diff out.txt result6.txt
	./main>out.txt test4.txt && diff out.txt result4.txt
	./main>out.txt test3.txt && diff out.txt result3.txt
	