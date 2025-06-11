#include <tools/vector.h>
#include <kernel.h>

vector_t vector_init(uintarch_t size) {
    vector_t vec = {
	.arr = kmalloc(size),
	.count = 0,
	.size = size,
	.cap = 1
    };
    return vec;
}
void vector_push_back(vector_t *this, void *item) {
    if (this->count + 1 >= this->cap) {
	uintarch_t cap = this->cap << 1;
	void *arr = kmalloc(cap * this->size);
	kmemcpy(arr, this->arr, this->cap * this->size);
	kfree(this->arr);
	this->arr = arr;
	this->cap = cap;
    }
    kmemcpy(this->arr + (this->count * this->size), item, this->size);
}
void vector_pop(vector_t *this) {
    --this->count;
}
void *vector_get(vector_t *this, uintarch_t index) {
    return this->arr + (index * this->size);
}
void vector_destroy(vector_t *this) {
    kfree(this->arr);
    kfree(this);
}
