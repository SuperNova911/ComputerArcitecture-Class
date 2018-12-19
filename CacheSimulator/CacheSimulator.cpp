#include "Cache.h"
#include <iostream>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
	// 입력 인자 개수 검사
	const int REQUIRE_ARGS = 4;
	if (argc != REQUIRE_ARGS + 1)
	{
		printf("입력 인자가 '%d'개가 아닙니다\n", REQUIRE_ARGS);
		return 0;
	}

	// 인자 받아오기
	char *traceFileName = argv[1];
	int cacheSize = atoi(argv[2]);
	int cacheBlockSize = atoi(argv[3]);
	int associativity = atoi(argv[4]);

	// 트레이스 파일 열기
	FILE *file;
	file = fopen(traceFileName, "r");

	// 잘못된 인자 예외 처리
	if (file == NULL)
	{
		printf("파일을 열 수 없습니다, file: '%s'\n", traceFileName);
		return 0;
	}
	if (cacheBlockSize & cacheBlockSize - 1)
	{
		printf("Cache block의 크기가 2의 지수승이 아닙니다, 입력: '%d'\n", cacheBlockSize);
		return 0;
	}
	if (associativity != 1 && associativity != 2 && associativity != 4 && associativity != 8)
	{
		printf("Associativity가 1, 2, 4, 8 이외의 값이 입력되었습니다, 입력: '%d'\n", associativity);
		return 0;
	}
	if (cacheSize % (cacheBlockSize * associativity) != 0)
	{
		printf("Cache 전체의 크기가 (CacheBlockSize) x (Associativity)의 배수가 아닙니다, 입력: '%d'\n", cacheSize);
		return 0;
	}

	// 새로운 캐시 클래스 생성
	Cache cache = Cache(cacheSize, cacheBlockSize, associativity);

	// 캐시의 tag, index, offset의 비트 수를 출력
	printf("tag: %d bits\nindex: %d bits\noffset: %d bits\n",
		cache.getTagBits(), cache.getIndexBits(), cache.getOffsetBits());
	
	// 트레이스파일에서 읽어올 필드들
	char mode[2];
	unsigned int address;	// 메모리 주소
	int value;

	char buffer[128];
	while (fgets(buffer, sizeof(buffer), file) != NULL)
	{
		// 트레이스 파일에서 한 줄을 읽어서 각 필드를 분리
		sscanf(buffer, "%s %x %d", mode, &address, &value);

		// 읽어온 메모리 주소를 캐시에서 접근
		cache.access(address);
	}

	// 트레이스 파일에 있는 메모리 접근이 끝나고 Hit 결과를 출력
	printf("Result: total access %d, hit %d, hit rate %.2lf\n", 
		cache.getAccessCount(), cache.getHitCount(), cache.getHitRate());

	return 0;
}