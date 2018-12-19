#pragma once
#include <bitset>
#include <list>

constexpr int ADDRESS_BITS = 32;	// 32비트 메모리 주소

using namespace std;

// 캐시 슬롯 구조체
typedef struct CacheSlot_t
{
	bitset<ADDRESS_BITS> tagBits;		// 슬롯의 Tag 비트
	bitset<1> validBit;					// valid 비트
} CacheSlot;

// 캐시 인덱스 슬롯 구조체
typedef struct CacheIndexSlot_t
{
	bitset<ADDRESS_BITS> indexBits;	// 인덱스 슬롯의 Index 비트

	list<int> LRU_list;		// LRU 슬롯을 찾기 위한 리스트
	int slotCount;			// 캐시 슬롯 개수
	CacheSlot *slotList;	// 캐시 슬롯 리스트
} CacheIndexSlot;

// 캐시 Hit 시뮬레이터 전용 캐시 클래스
class Cache
{
private:
	int size;			// 캐시 크기
	int blockSize;		// 블럭 크기
	int associativity;	// associativity

	int tagBits;		// Tag 비트 수
	int indexBits;		// Index 비트 수
	int offsetBits;		// Offset 비트 수

	int accessCount;	// 캐시 접근 횟수
	int hitCount;		// Hit count

	CacheIndexSlot *indexSlotList;	// 캐시 세트 리스트

public:
	Cache(int size, int blockSize, int associativity);	// 생성자
	void access(unsigned int address);					// 캐시에 address 주소로 접근

	int getTagBits();		// Tag 비트 값 반환
	int getIndexBits();		// Index 비트 값 반환
	int getOffsetBits();	// Offset 비트 값 반환

	int getAccessCount();	// 캐시 접근 횟수 반환
	int getHitCount();		// Hit count 값 반환
	float getHitRate();		// Hit rate 계산 한 값 반환
};