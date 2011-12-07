object = kmeans.o meancluster.o
kmeans:$(object)
	cc -o kmeans $(object) -lm
kmeans.o:kmeans.c kmeans.h
	cc -c kmeans.c kmeans.h -lm
meancluster.o:meancluster.c kmeans.h
	cc -c meancluster.c kmeans.h -lm

clean:
	rm  kmeans $(object)

