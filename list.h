class OutOfBoundError{};


template <class T>
class list{
    public:
		virtual int search(const T & x) const = 0;
		virtual T visit(int i) const = 0;
		virtual void traverse() const = 0;
		virtual int length() const = 0;
		virtual void clear() = 0;
		virtual void insert(int i, const T &x) = 0;
		virtual void remove(int i) = 0;
		virtual ~list()= default;;
};
