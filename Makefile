all:
	g++ -o main FrameBuffer.cpp Point.cpp Line.cpp Polygon.cpp Window.cpp ThreeDimension.cpp View.cpp Curve.cpp Face.cpp main.cpp

run:
	./main

clean:
	rm main
