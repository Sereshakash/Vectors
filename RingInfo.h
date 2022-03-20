void* sumInt(void* a1, void* a2);
void* sumFloat(void* a1, void* a2);
void* sumComplex(void* a1, void* a2);
void* multInt(void* a1, void* a2);
void* multFloat(void* a1, void* a2);
void* multComplex(void* a1, void* a2);
void* minusInt(void* a1);
void* minusFloat(void* a1);
void* minusComplex(void* a1);

struct RingInfo {
	size_t size;
	void* (*sum)(void*, void*);
	void* zero;
	void* (*minus)(void*);
	void* (*mult)(void*, void*);
	void* one;
};
struct RingInfo* Create(	
	size_t size,
	void* (*sum)(void*, void*),
	void* zero,
	void* (*minus)(void*),
	void* (*mult)(void*, void*),
	void* one);

struct VectorN
{
	struct RingInfo* ringInfo;
	int N;
	void* elements;
	int datatype;
};

void* GetNelement(struct VectorN* vect, int n);
void * CreateElements(struct RingInfo* ringInfo, int N, int datatype);
struct VectorN* CreateVector (struct RingInfo* ringInfo, int N, int datatype, void * numbers);
void PrintVector(struct VectorN* vector);
void DeleteVector(struct VectorN* vector);