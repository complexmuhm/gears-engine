#pragma once
#include <bitset>
#include <queue>

class Keyboard
{
	friend class Window;

public:
	struct Event
	{
		enum class Type
		{
			Pressed,
			Released,
			Character,
			Invalid
		};
		Event(Type type, unsigned char key)
			:type(type), key(key)
		{}

		Event()
			:type(Type::Invalid), key(0)
		{}

		bool is_valid() const
		{
			return type != Type::Invalid;
		}

		Type type;
		unsigned char key;
	};

public:
	Keyboard();
	~Keyboard();

	bool is_key_pressed(unsigned char key) const;
	bool is_autorepeat_set() const;
	bool is_key_empty();
	bool is_char_empty();

	Keyboard::Event pop();
	char pop_char();

	void clear_events();
	void set_autorepeat(bool state);

private:
	void on_key_pressed(unsigned char key);
	void on_key_released(unsigned char key);
	void on_char(char character);
	void clear_state(); //Clears the key bitset

	template<typename T>
	void trim_buffer(std::queue<T>& q);

private:
	static const unsigned int key_size = 256;
	static const unsigned int max_buffer_size = 32;

	bool autorepeat;
	std::bitset<key_size> keys;
	std::queue<Event> event_buffer;
	std::queue<char> char_buffer;
};


template<typename T>
inline void Keyboard::trim_buffer(std::queue<T>& q)
{
	while (q.size() > max_buffer_size)
	{
		q.pop();
	}
}
