template <typename T, typename Comp>
void MyHeap<T, Comp>::sift_down(int n) {
  while (!is_leaf(n))
  {
    int largerChild = lc(n);
    int rChild = rc(n);

    if ((rChild < m_size) && (Comp::prior(m_data[rChild], m_data[largerChild])))
      largerChild = rChild;

    if (Comp::prior(m_data[n], m_data[largerChild]))
      return;

    swap(m_data[n], m_data[largerChild]);

    n = largerChild;
  }
}

template <typename T, typename Comp>
MyHeap<T, Comp>::MyHeap(const T arr[], const int size) {
  if (size > 0)
  {
    m_size = size;
    m_data = new T[m_size * 2];
    m_maxsize = m_size * 2;
    for (int i = 0; i < m_size; i++)
      m_data[i] = arr[i];
    heapify();
  }
  else
  {
    m_size = 0;
    m_maxsize = 0;
    m_data = nullptr;
  }
}

template <typename T, typename Comp>
MyHeap<T, Comp>::MyHeap(const MyHeap<T, Comp>& src) {
  m_size = src.m_size;
  m_maxsize = src.m_maxsize;
  m_data = new T[src.m_size];
  for (int i = 0; i < m_size; i++)
    m_data[i] = src.m_data[i];
}

template <typename T, typename Comp>
MyHeap<T, Comp>& MyHeap<T, Comp>::operator=(const MyHeap<T, Comp>& src) {
  m_size = src.m_size;
  m_maxsize = src.m_maxsize;
  delete[] m_data;
  m_data = new T[src.m_size];
  for (int i = 0; i < m_size; i++)
    m_data[i] = src.m_data[i];
}

template <typename T, typename Comp>
T& MyHeap<T, Comp>::top() {
  return m_data[0];
}

template <typename T, typename Comp>
void MyHeap<T, Comp>::pop() {
  if (m_size == 0)
    return;

  swap(m_data[0], m_data[--m_size]);

  if (m_size != 0)
    sift_down(0);

  if (m_size <= m_maxsize*(1.0/4))
    shrink_to_fit();
}

template <typename T, typename Comp>
void MyHeap<T, Comp>::push(const T& it){
  if (m_maxsize == 0)
    reserve(m_maxsize+1);
  else if (m_size == m_maxsize)
    reserve(m_maxsize * 2);

  m_data[m_size] = it;
  int pos = m_size++;

  while((pos != 0) && (Comp::prior(m_data[pos], m_data[parent(pos)])))
  {
    swap(m_data[pos], m_data[parent(pos)]);

    pos = parent(pos);
  }
}

template <typename T, typename Comp>
void MyHeap<T, Comp>::reserve(int size) {
  MyHeap<T, Comp> temp = *this;
  delete[] m_data;
  m_data = new T[size];
  m_maxsize = size;
  for (int i = 0; i < temp.size(); i++)
    m_data[i] = temp.m_data[i];
}

template <typename T, typename Comp>
void MyHeap<T, Comp>::shrink_to_fit() {
  if (m_size != 0 && (m_size <= m_maxsize*(1.0/4)))
  {
    MyHeap<T, Comp> temp = *this;
    delete[] m_data;
    m_data = new T[temp.m_size*2];
    m_maxsize = m_size*2;
    for (int i = 0; i < temp.size(); i++)
      m_data[i] = temp.m_data[i];
  }
  else if (m_size == 0 && (m_size <= m_maxsize*(1.0/4)))
  {
    delete[] m_data;
    m_data = nullptr;
    m_maxsize = 0;
  }
}

template <typename T, typename Comp>
int MyHeap<T, Comp>::parent(const int n) {
  return ((n - 1) / 2);
}

template <typename T, typename Comp>
bool MyHeap<T, Comp>::is_leaf(const int n) {
  return ((n >= m_size/2) && (n < m_size));
}

template <typename T, typename Comp>
int MyHeap<T, Comp>::rc(const int n) {
  return ((2 * n) + 2);
}

template <typename T, typename Comp>
int MyHeap<T, Comp>::lc(const int n) {
  return ((2 * n) + 1);
}

template <typename T, typename Comp>
void MyHeap<T, Comp>::heapify() {
  for (int i = parent(m_size-1); i >= 0; i--)
    sift_down(i);
}

template <typename T, typename Comp>
void MyHeap<T, Comp>::print() {
  MyHeap<T, Comp> cpy(*this);
  while (cpy.size() > 0)
  {
    std::cout << cpy.top() << " ";
    cpy.pop();
  }
}
