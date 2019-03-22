#include "stdio.h"
#include "string.h"
#include "math.h"
#include "time.h"
#define BUFFER_SIZE 100

int N, min_cols[20 + 1], cols[20 + 1], spot[20][2];
float min_dist;

void reset_min();
float distance(int a, int b);
bool promising(int level, float dist);
void TSP(int level);
void load();

int main()
{
	char buffer[BUFFER_SIZE];
	while (1) {
		printf("$ ");
		scanf("%s", buffer);
		if (strcmp(buffer, "read") == 0)
			load();
		else if (strcmp(buffer, "exit") == 0)
			break;
	}
	return 0;
}

void reset_min()
{
	min_dist = 0;
	for (int i = 0; i < N - 1; i++)
		min_dist += distance(i, i + 1);
	min_dist += distance(0, N - 1);
}
float distance(int a, int b)
{
	float j = (spot[a][0] - spot[b][0]);
	float k = (spot[a][1] - spot[b][1]);
	j *= j;
	k *= k;
	return sqrt(j + k);
}
bool promising(int level, float dist = 0)
{
	for (int i = 1; i < level; i++) {
		if (cols[i] == cols[level])
			return false;
	}
	for (int i = 1; i < level; i++)
		dist += distance(cols[i], cols[i + 1]);
	dist += distance(cols[1], cols[level]);
	if (dist > min_dist) return false;
	return true;
}

void TSP(int level)
{
	float dist = 0;
	if (!promising(level, dist))
		return;
	else if (level == N) {
		for (int i = 1; i < N; i++)
			dist += distance(cols[i], cols[i + 1]);
		dist += distance(cols[1], cols[N]);
		/////////////test////////////////
		//for (int i = 1; i <= N; i++)
		//printf("%d ", cols[i]);
		//printf(" %f\n", dist);
		////////////////////////////////
		if (dist < min_dist) {
			min_dist = dist;
			for (int i = 1; i <= N; i++)
				min_cols[i] = cols[i];
		}
		return;
	}
	for (int i = 1; i < N; i++)
	{
		cols[level + 1] = i;
		TSP(level + 1);
	}
	return;
}
void load()
{
	char fileName[BUFFER_SIZE];
	scanf("%s", fileName);
	FILE *fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}

	fscanf(fp, "%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < 2; j++)
			fscanf(fp, "%d", &spot[i][j]);
	fclose(fp);
	int start = clock();
	reset_min();
	TSP(1);
	printf("%.14f\n", min_dist);
	for (int i = 1; i <= N; i++)
		printf("%d ", min_cols[i]);
	printf("\n");
	int end = clock();
	printf("time : %d\n\n", end - start);
}