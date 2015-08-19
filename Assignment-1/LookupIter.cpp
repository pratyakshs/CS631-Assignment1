#include "LookupIter.h"

LookupIter::LookupIter(char *_key, KeyType _keyType, TreeNode *_node, int _position, int _payloadLen) {
    key = _key;
    keyType = _keyType;
    node = _node;
    position = _position;
    payloadlen = _payloadLen;
    nullIter = false;
}

LookupIter::LookupIter() {
    nullIter = true;
}

bool LookupIter::isNull() {
    return nullIter;
}

bool LookupIter::hasNext() {

    int next_pos = position + 1;
    if (next_pos >= node->numkeys) {
    	/* Reached end of node */
    	return false;
    }
    if (strncmp(&(node->data[next_pos*keylen(&keyType)]), key, keylen(&keyType)) != 0) {
    	/* The key at next position doesn't match the iterator's key*/
    	return false;
    }
    return true;
}

int LookupIter::next() {
    if (hasNext()) {
    	position++;
    	return 0;
    }
    else return -1;
}

int LookupIter::get(char *payload) {
	/* TODO: Checks */
	/* TODO: Advance position?*/
    strncpy(payload, &(node->data[DATA_SIZE-(position+1)*payloadlen]), payloadlen);
    return 0;
}
