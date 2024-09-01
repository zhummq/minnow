
#include "reassembler.hh"



using namespace std;

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring )
{
  // Your code here.
  uint64_t last_index = first_index + data.size();
  uint64_t first_unacceptable_index = first_unassembled_index_ + writer().available_capacity();

  
  if (is_last_substring){
    final_index_ = first_index + data.size();
  }

  if (first_index < first_unassembled_index_){
    if (last_index <= first_unassembled_index_){
      check_push();
      return;
    } else {
      
      data = data.erase(0,first_unassembled_index_ - first_index);
      first_index = first_unassembled_index_;
    }
  }
  if (first_unacceptable_index <= first_index){
    return;
  }
  if ( last_index > first_unacceptable_index ) {
    data.erase( first_unacceptable_index - first_index );
  }

  if (!segments_.empty()){
    auto cur = segments_.lower_bound(Seg(first_index, ""));
    if (cur != segments_.begin()){
      cur--;
      if (cur->first_index + cur->data.size() > first_index){
        
        data = data.erase(0, cur->first_index + cur->data.size() - first_index);
        first_index += cur->first_index + cur->data.size() - first_index;
      }
    }
    cur = segments_.lower_bound(Seg(first_index, ""));
    while (cur != segments_.end() && cur->first_index < last_index){
      if (cur->first_index + cur->data.size() <= last_index){
        
        bytes_pending_ -= cur->data.size();
        segments_.erase(cur);
        cur = segments_.lower_bound(Seg(first_index, ""));
      } else {
        data = data.erase(cur->first_index - first_index, string::npos);
        break;
      }
    }
  }

  bytes_pending_ += data.size();
  segments_.insert(Seg(first_index, data));
  check_push();
}

uint64_t Reassembler::bytes_pending() const
{
  // Your code here.
  return bytes_pending_;
}



void Reassembler:: check_push(){
  while (!segments_.empty() ){
    auto seg = segments_.begin();
    if (seg->first_index == first_unassembled_index_){
      output_.writer().push(seg->data);
    first_unassembled_index_ += seg->data.size();
    bytes_pending_ -= seg->data.size();
    auto tmp = seg;
    segments_.erase(tmp);
    if (first_unassembled_index_ >= final_index_){
      output_.writer().close();
    }
    } else
    break;
    
  }
}
