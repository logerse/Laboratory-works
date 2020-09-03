struct Node_st {
  int value;
  int row;
  int column;
  Node_st *next;

  Node_st(const int row_, const int column_, const int value_) 
	  : value {value_}, row {row_}, column {column_}, next {nullptr} {} 

  bool operator!= (const Node_st ns) { return (row != ns.row) || (column != ns.column); };
};



struct LinkedList {
  Node_st* HEAD;
  Node_st* TAIL;
  char *buffer = nullptr;	

  LinkedList(void) : HEAD {nullptr}, TAIL {HEAD} {};

  void PushBack(const int row, const int column, const int value) {
    if(HEAD == nullptr) {
      HEAD = new Node_st(row, column, value);
      TAIL = HEAD;
      return;

    } else {
      TAIL->next = new Node_st(row, column, value);
      TAIL = TAIL->next;
    };
  };

  int DeleteNode(const  Node_st* node) {
    if(node != nullptr && FindElement(node->row, node->column) != nullptr)
      DeleteNd(*node);
    else
      return -1;
    return 0;
  };

  Node_st* FindElement(const int row, const int column) const {
    Node_st* cur = HEAD;
    while(cur != nullptr) {
      if(cur->row == row && cur->column == column) break;
      cur = cur->next;
    };

    return cur;
  };

  void Destruct(void) {
    Node_st* cur = HEAD, *next;
    for(;;) {
      if(cur == nullptr) break;
      next = cur->next;
      delete cur;
      cur = next;
    };
    if(buffer != nullptr) delete[] buffer;
  };

  ~LinkedList(void) { 
    Destruct();
  };

private:
  void DeleteNd(const Node_st node) {
    Node_st* cur = HEAD, *prev;
    while(cur != nullptr && *cur != node) {
      prev = cur;
      cur = cur->next;
    };

    prev->next = cur->next;
    delete cur;
  };
};
