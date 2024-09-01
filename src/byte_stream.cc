#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ) {
  buffer_.reserve( capacity);
}

bool Writer::is_closed() const
{
  // Your code here.
  return is_closed_;
}

void Writer::push( string data )
{
  // Your code here.
  size_t bytes_to_copy = min( data.size(), available_capacity() );
  buffer_ += data.substr( 0, bytes_to_copy );
  bytes_pushed_ += bytes_to_copy;
  return;
}

void Writer::close()
{
  // Your code here.
  is_closed_ = true;
}

uint64_t Writer::available_capacity() const
{
  // Your code here.
  return capacity_ - buffer_.size();
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return bytes_pushed_;
}

bool Reader::is_finished() const
{
  // Your code here.
  return ((is_closed_ == true)&&(bytes_buffered() == 0));
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return bytes_popped_;
}

string_view Reader::peek() const
{
  // Your code here.
  string_view sv( buffer_.data() , min(static_cast<uint64_t>(1000),this->bytes_buffered()));
  return sv;
}

void Reader::pop( uint64_t len )
{
  // Your code here.
  buffer_.erase(buffer_.begin(),buffer_.begin()+len);
  bytes_popped_ += len;
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return buffer_.size();
}
