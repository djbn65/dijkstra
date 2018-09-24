template <typename T>
void swap(T &item1, T &item2) {
  T temp = item1;
  item1 = item2;
  item2 = temp;

  return;
}

template <typename T>
MyList<T>::MyList() {
  m_size = 0;
  m_head = new Node<T>(T(),nullptr,nullptr);
  m_tail = new Node<T>(T(),m_head,nullptr);
  m_head->m_next = m_tail;
}

template <typename T>
MyList<T>::~MyList() {
  Node<T>* temp;
  while (m_head != nullptr) {
    temp = m_head;
    m_head = m_head->m_next;
    delete temp;
  }
}

template <typename T>
MyList<T>& MyList<T>::operator=(const MyList<T> &source) {
  clear();
  Node<T>* curr = source.m_head->m_next;
  for (int i = 0; i < source.m_size; i++)
  {
    push_back(curr->m_element);
    curr = curr->m_next;
  }

  return *this;
}

template <typename T>
MyList<T>::MyList(const MyList<T> &source) {
  m_size = 0;
  m_head = new Node<T>(T(),nullptr,nullptr);
  m_tail = new Node<T>(T(),m_head,nullptr);
  m_head->m_next = m_tail;
  Node<T>* curr = source.m_head->m_next;
  for (int i = 0; i < source.m_size; i++)
  {
    push_back(curr->m_element);
    curr = curr->m_next;
  }
}

template <typename T>
T& MyList<T>::front() {
  return m_head->m_next->m_element;
}

template <typename T>
T& MyList<T>::back() {
  return m_tail->m_prev->m_element;
}

template <typename T>
void MyList<T>::assign(int count, const T& value) {
  clear();
  if (count <= 0)
  {
    return;
  }
  for (int i = 0; i < count; i++)
    push_front(value);

  m_size = count;
}

template <typename T>
void MyList<T>::clear() {
  Node<T>* temp;
  while (m_head != nullptr) {
    temp = m_head;
    m_head = m_head->m_next;
    delete temp;
  }
  m_size = 0;
  m_head = new Node<T>(T(),nullptr,nullptr);
  m_tail = new Node<T>(T(),m_head,nullptr);
  m_head->m_next = m_tail;
}

template <typename T>
void MyList<T>::push_front(const T& x) {
  insert(0,x);
}

template <typename T>
void MyList<T>::push_back(const T& x) {
  insert(m_size,x);
}

template <typename T>
void MyList<T>::pop_back() {
  if (empty())
    return;
  Node<T>* temp = m_tail->m_prev;
  m_tail->m_prev = m_tail->m_prev->m_prev;
  m_tail->m_prev->m_next = m_tail;
  delete temp;
  m_size--;
}

template <typename T>
void MyList<T>::insert(int i, const T& x) {
  if (empty())
  {
    m_head->m_next = m_tail->m_prev = new Node<T>(x,m_head,m_tail);
  }
  else if (i < 0 || i > m_size)
  {
    return;
  }
  else
  {
    Node<T>* curr = m_head;
    Node<T>* temp;
    for (int x = 0; x <= i; x++)
    {
      curr = curr->m_next;
    }
    temp = curr->m_prev;
    curr->m_prev = temp->m_next = new Node<T>(x,temp,curr);
  }
  m_size++;
}

template <typename T>
T& MyList<T>::operator[](int i) {
  if (!empty() && i >= 0 && i < m_size)
  {
    Node<T>* curr = m_head->m_next;
    for (int x = 0; x < i; x++)
      curr = curr->m_next;
    return curr->m_element;
  }
  else
  {
    return m_head->m_element;
  }
}

template <typename T>
void MyList<T>::remove(T i) {
  Node<T>* curr = m_head->m_next;
  Node<T>* temp;
  while (curr != m_tail)
  {
    if (curr->m_element == i)
    {
      temp = curr;
      curr->m_prev->m_next = curr->m_next;
      curr->m_next->m_prev = curr->m_prev;
      delete temp;
      m_size--;
    }
    curr = curr->m_next;
  }

  return;
}

template <typename T>
void MyList<T>::erase(int i) {
  Node<T>* curr = m_head->m_next;
  Node<T>* temp;
  if (i < 0 || i > m_size)
  {
    cout << "Index out of bounds. Item not erased" << endl;
    return;
  }
  else if (empty())
  {
    cout << "List empty. Can't remove item" << endl;
    return;
  }
  else
  {
    for (int j = 0; j < i; j++)
      curr = curr->m_next;

    temp = curr;
    curr->m_prev->m_next = curr->m_next;
    curr->m_next->m_prev = curr->m_prev;
    delete temp;
    m_size--;
  }
}

template <typename T>
void MyList<T>::reverse() {
  Node<T>* curr = m_head->m_next;
  Node<T>* temp;
  for (int i = 0; i < m_size; i++)
  {
    temp = curr;
    curr = curr->m_next;
    swap(temp->m_next,temp->m_prev);
  }
  swap(m_head->m_next,m_head->m_prev);
  swap(m_tail->m_next,m_tail->m_prev);
  swap(m_head, m_tail);
}

template <typename T>
void MyList<T>::resize(int count) {
  if (count == m_size || count < 0)
  {
    return;
  }
  else if (count == 0)
  {
    clear();
  }
  else if (count > m_size)
  {
    int j = count-m_size;
    for (int i = 0; i < j; i++)
      push_back(T());
  }
  else
  {
    int j = m_size-count;
    for (int i = 0; i < j; i++)
      pop_back();
  }
}

template <typename T>
bool MyList<T>::empty() {
  return m_size == 0;
}

template <typename T>
int MyList<T>::size() {
  return m_size;
}
