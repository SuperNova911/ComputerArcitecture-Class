#include "Cache.h"
#include <math.h>

// 캐시의 크기, 블럭크기, associativity를 매개변수로 받아 새로운 캐시 생성
// [매개변수] size: 캐시크기, blockSize: 블럭크기, associativity: associativity
Cache::Cache(int size, int blockSize, int associativity)
{
	// 캐시 설정
	this->size = size;
	this->blockSize = blockSize;
	this->associativity = associativity;

	// Tag, Index, Offset 비트 수 계산
	int set = size / blockSize / associativity;
	indexBits = (int)log2(set);
	offsetBits = (int)log2(blockSize);
	tagBits = ADDRESS_BITS - indexBits - offsetBits;

	// 메모리 접근 횟수, hit count 초기화
	accessCount = 0;
	hitCount = 0;

	// 캐시 블럭들을 만들고 초기화
	indexSlotList = new CacheIndexSlot[set];
	for (int index = 0; index < set; index++)
	{
		// 캐시 인덱스 슬롯 값 설정
		indexSlotList[index].indexBits = index << offsetBits;
		indexSlotList[index].slotCount = associativity;
		indexSlotList[index].slotList = new CacheSlot[associativity];

		// 캐시 슬롯 초기화
		for (int slotIndex = 0; slotIndex < associativity; slotIndex++)
		{
			indexSlotList[index].slotList[slotIndex].tagBits = slotIndex;
			indexSlotList[index].slotList[slotIndex].validBit = 0;
		}
	}
}

// 매개변수로 전달 받은 주소에 접근 시도
// [매개변수] address: 접근 할 주소 값
void Cache::access(unsigned int address)
{
	// 캐시 접근 횟수를 증가
	accessCount++;

	// 매개변수로 받은 주소값에서 Index 비트를 추출
	bitset<ADDRESS_BITS> address_index = address;
	address_index = (address_index >> offsetBits) << offsetBits;
	address_index = (address_index << tagBits) >> tagBits;

	// 매개변수로 받은 주소값에서 Tag 비트를 추출
	bitset<ADDRESS_BITS> address_tag = address;
	address_tag = (address_tag >> offsetBits + indexBits) << offsetBits + indexBits;

	// 캐시에서 매개변수로 받은 주소값의 Index 비트에 해당하는 인덱스 슬롯의 포인터를 가져옴
	CacheIndexSlot *targetSet = &indexSlotList[(address_index >> offsetBits).to_ulong()];

	// 해당 인덱스 슬롯에 Tag 비트가 일치하는 캐시 슬롯이 있는지 검사
	for (int index = 0; index < targetSet->slotCount; index++)
	{
		// Compulsory Miss (캐시 슬롯의 valid bit가 0)
		if (targetSet->slotList[index].validBit == 0)
		{
			// validBit 1로 변경, 슬롯의 Tag 비트 설정
			targetSet->slotList[index].tagBits = address_tag;
			targetSet->slotList[index].validBit = 1;

			// 해당 슬롯을 LRU 리스트 맨 앞에 추가
			targetSet->LRU_list.push_front(index);
			return;
		}

		// Hit (캐시 슬롯의 Tag 비트와 매개변수로 받은 주소의 Tag 비트가 일치)
		if (targetSet->slotList[index].tagBits == address_tag)
		{
			// 해당 슬롯을 LRU 리스트 맨 앞으로 이동
			targetSet->LRU_list.remove(index);		
			targetSet->LRU_list.push_front(index);
			
			// Hit 회수 증가
			hitCount++;
			return;
		}
	}
	// Tag 비트가 일치하는 캐시 슬롯이 없으면

	// LRU 리스트에서 가장 오래 전에 쓰인 슬롯을 가져옴
	int targetIndex = targetSet->LRU_list.back();

	// Conflict Miss (해당 슬롯의 Tag 비트를 새로운 주소의 Tag로 변경)
	targetSet->slotList[targetIndex].tagBits = address_tag;

	// 해당 슬롯을 LRU 리스트 맨 앞으로 이동
	targetSet->LRU_list.remove(targetIndex);
	targetSet->LRU_list.push_front(targetIndex);
}

// Tag 비트 값 반환
int Cache::getTagBits()
{
	return tagBits;
}

// Index 비트 값 반환
int Cache::getIndexBits()
{
	return indexBits;
}

// Offset 비트 값 반환
int Cache::getOffsetBits()
{
	return offsetBits;
}

// 캐시 접근 횟수 반환
int Cache::getAccessCount()
{
	return accessCount;
}

// Hit count 값 반환
int Cache::getHitCount()
{
	return hitCount;
}

// Hit rate 계산 한 값 반환
float Cache::getHitRate()
{
	return (float)hitCount / accessCount;
}
