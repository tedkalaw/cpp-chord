/**
 * Autogenerated by Thrift Compiler (0.8.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef Chord_H
#define Chord_H

#include <TProcessor.h>
#include "mp2_types.h"

namespace mp2 {

class ChordIf {
 public:
  virtual ~ChordIf() {}
  virtual void add_node() = 0;
  virtual void add_file() = 0;
  virtual void del_file() = 0;
  virtual void get_file() = 0;
  virtual void get_table() = 0;
  virtual void join_network(successor& _return, const int32_t pid) = 0;
  virtual void current_pred(predecessor& _return) = 0;
  virtual void notify(const int32_t pid, const int32_t new_port) = 0;
  virtual void find_successor(successor& _return, const int32_t pid) = 0;
  virtual void find_predecessor(neighbor& _return, const int32_t pid) = 0;
  virtual void closest_preceding_finger(neighbor& _return, const int32_t pid) = 0;
  virtual void get_info(neighbor& _return) = 0;
};

class ChordIfFactory {
 public:
  typedef ChordIf Handler;

  virtual ~ChordIfFactory() {}

  virtual ChordIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(ChordIf* /* handler */) = 0;
};

class ChordIfSingletonFactory : virtual public ChordIfFactory {
 public:
  ChordIfSingletonFactory(const boost::shared_ptr<ChordIf>& iface) : iface_(iface) {}
  virtual ~ChordIfSingletonFactory() {}

  virtual ChordIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(ChordIf* /* handler */) {}

 protected:
  boost::shared_ptr<ChordIf> iface_;
};

class ChordNull : virtual public ChordIf {
 public:
  virtual ~ChordNull() {}
  void add_node() {
    return;
  }
  void add_file() {
    return;
  }
  void del_file() {
    return;
  }
  void get_file() {
    return;
  }
  void get_table() {
    return;
  }
  void join_network(successor& /* _return */, const int32_t /* pid */) {
    return;
  }
  void current_pred(predecessor& /* _return */) {
    return;
  }
  void notify(const int32_t /* pid */, const int32_t /* new_port */) {
    return;
  }
  void find_successor(successor& /* _return */, const int32_t /* pid */) {
    return;
  }
  void find_predecessor(neighbor& /* _return */, const int32_t /* pid */) {
    return;
  }
  void closest_preceding_finger(neighbor& /* _return */, const int32_t /* pid */) {
    return;
  }
  void get_info(neighbor& /* _return */) {
    return;
  }
};


class Chord_add_node_args {
 public:

  Chord_add_node_args() {
  }

  virtual ~Chord_add_node_args() throw() {}


  bool operator == (const Chord_add_node_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const Chord_add_node_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_add_node_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_add_node_pargs {
 public:


  virtual ~Chord_add_node_pargs() throw() {}


  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_add_node_result {
 public:

  Chord_add_node_result() {
  }

  virtual ~Chord_add_node_result() throw() {}


  bool operator == (const Chord_add_node_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const Chord_add_node_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_add_node_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_add_node_presult {
 public:


  virtual ~Chord_add_node_presult() throw() {}


  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};


class Chord_add_file_args {
 public:

  Chord_add_file_args() {
  }

  virtual ~Chord_add_file_args() throw() {}


  bool operator == (const Chord_add_file_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const Chord_add_file_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_add_file_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_add_file_pargs {
 public:


  virtual ~Chord_add_file_pargs() throw() {}


  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_add_file_result {
 public:

  Chord_add_file_result() {
  }

  virtual ~Chord_add_file_result() throw() {}


  bool operator == (const Chord_add_file_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const Chord_add_file_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_add_file_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_add_file_presult {
 public:


  virtual ~Chord_add_file_presult() throw() {}


  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};


class Chord_del_file_args {
 public:

  Chord_del_file_args() {
  }

  virtual ~Chord_del_file_args() throw() {}


  bool operator == (const Chord_del_file_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const Chord_del_file_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_del_file_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_del_file_pargs {
 public:


  virtual ~Chord_del_file_pargs() throw() {}


  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_del_file_result {
 public:

  Chord_del_file_result() {
  }

  virtual ~Chord_del_file_result() throw() {}


  bool operator == (const Chord_del_file_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const Chord_del_file_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_del_file_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_del_file_presult {
 public:


  virtual ~Chord_del_file_presult() throw() {}


  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};


class Chord_get_file_args {
 public:

  Chord_get_file_args() {
  }

  virtual ~Chord_get_file_args() throw() {}


  bool operator == (const Chord_get_file_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const Chord_get_file_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_get_file_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_get_file_pargs {
 public:


  virtual ~Chord_get_file_pargs() throw() {}


  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_get_file_result {
 public:

  Chord_get_file_result() {
  }

  virtual ~Chord_get_file_result() throw() {}


  bool operator == (const Chord_get_file_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const Chord_get_file_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_get_file_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_get_file_presult {
 public:


  virtual ~Chord_get_file_presult() throw() {}


  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};


class Chord_get_table_args {
 public:

  Chord_get_table_args() {
  }

  virtual ~Chord_get_table_args() throw() {}


  bool operator == (const Chord_get_table_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const Chord_get_table_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_get_table_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_get_table_pargs {
 public:


  virtual ~Chord_get_table_pargs() throw() {}


  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_get_table_result {
 public:

  Chord_get_table_result() {
  }

  virtual ~Chord_get_table_result() throw() {}


  bool operator == (const Chord_get_table_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const Chord_get_table_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_get_table_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_get_table_presult {
 public:


  virtual ~Chord_get_table_presult() throw() {}


  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _Chord_join_network_args__isset {
  _Chord_join_network_args__isset() : pid(false) {}
  bool pid;
} _Chord_join_network_args__isset;

class Chord_join_network_args {
 public:

  Chord_join_network_args() : pid(0) {
  }

  virtual ~Chord_join_network_args() throw() {}

  int32_t pid;

  _Chord_join_network_args__isset __isset;

  void __set_pid(const int32_t val) {
    pid = val;
  }

  bool operator == (const Chord_join_network_args & rhs) const
  {
    if (!(pid == rhs.pid))
      return false;
    return true;
  }
  bool operator != (const Chord_join_network_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_join_network_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_join_network_pargs {
 public:


  virtual ~Chord_join_network_pargs() throw() {}

  const int32_t* pid;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Chord_join_network_result__isset {
  _Chord_join_network_result__isset() : success(false) {}
  bool success;
} _Chord_join_network_result__isset;

class Chord_join_network_result {
 public:

  Chord_join_network_result() {
  }

  virtual ~Chord_join_network_result() throw() {}

  successor success;

  _Chord_join_network_result__isset __isset;

  void __set_success(const successor& val) {
    success = val;
  }

  bool operator == (const Chord_join_network_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const Chord_join_network_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_join_network_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Chord_join_network_presult__isset {
  _Chord_join_network_presult__isset() : success(false) {}
  bool success;
} _Chord_join_network_presult__isset;

class Chord_join_network_presult {
 public:


  virtual ~Chord_join_network_presult() throw() {}

  successor* success;

  _Chord_join_network_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};


class Chord_current_pred_args {
 public:

  Chord_current_pred_args() {
  }

  virtual ~Chord_current_pred_args() throw() {}


  bool operator == (const Chord_current_pred_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const Chord_current_pred_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_current_pred_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_current_pred_pargs {
 public:


  virtual ~Chord_current_pred_pargs() throw() {}


  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Chord_current_pred_result__isset {
  _Chord_current_pred_result__isset() : success(false) {}
  bool success;
} _Chord_current_pred_result__isset;

class Chord_current_pred_result {
 public:

  Chord_current_pred_result() {
  }

  virtual ~Chord_current_pred_result() throw() {}

  predecessor success;

  _Chord_current_pred_result__isset __isset;

  void __set_success(const predecessor& val) {
    success = val;
  }

  bool operator == (const Chord_current_pred_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const Chord_current_pred_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_current_pred_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Chord_current_pred_presult__isset {
  _Chord_current_pred_presult__isset() : success(false) {}
  bool success;
} _Chord_current_pred_presult__isset;

class Chord_current_pred_presult {
 public:


  virtual ~Chord_current_pred_presult() throw() {}

  predecessor* success;

  _Chord_current_pred_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _Chord_notify_args__isset {
  _Chord_notify_args__isset() : pid(false), new_port(false) {}
  bool pid;
  bool new_port;
} _Chord_notify_args__isset;

class Chord_notify_args {
 public:

  Chord_notify_args() : pid(0), new_port(0) {
  }

  virtual ~Chord_notify_args() throw() {}

  int32_t pid;
  int32_t new_port;

  _Chord_notify_args__isset __isset;

  void __set_pid(const int32_t val) {
    pid = val;
  }

  void __set_new_port(const int32_t val) {
    new_port = val;
  }

  bool operator == (const Chord_notify_args & rhs) const
  {
    if (!(pid == rhs.pid))
      return false;
    if (!(new_port == rhs.new_port))
      return false;
    return true;
  }
  bool operator != (const Chord_notify_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_notify_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_notify_pargs {
 public:


  virtual ~Chord_notify_pargs() throw() {}

  const int32_t* pid;
  const int32_t* new_port;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_notify_result {
 public:

  Chord_notify_result() {
  }

  virtual ~Chord_notify_result() throw() {}


  bool operator == (const Chord_notify_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const Chord_notify_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_notify_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_notify_presult {
 public:


  virtual ~Chord_notify_presult() throw() {}


  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _Chord_find_successor_args__isset {
  _Chord_find_successor_args__isset() : pid(false) {}
  bool pid;
} _Chord_find_successor_args__isset;

class Chord_find_successor_args {
 public:

  Chord_find_successor_args() : pid(0) {
  }

  virtual ~Chord_find_successor_args() throw() {}

  int32_t pid;

  _Chord_find_successor_args__isset __isset;

  void __set_pid(const int32_t val) {
    pid = val;
  }

  bool operator == (const Chord_find_successor_args & rhs) const
  {
    if (!(pid == rhs.pid))
      return false;
    return true;
  }
  bool operator != (const Chord_find_successor_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_find_successor_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_find_successor_pargs {
 public:


  virtual ~Chord_find_successor_pargs() throw() {}

  const int32_t* pid;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Chord_find_successor_result__isset {
  _Chord_find_successor_result__isset() : success(false) {}
  bool success;
} _Chord_find_successor_result__isset;

class Chord_find_successor_result {
 public:

  Chord_find_successor_result() {
  }

  virtual ~Chord_find_successor_result() throw() {}

  successor success;

  _Chord_find_successor_result__isset __isset;

  void __set_success(const successor& val) {
    success = val;
  }

  bool operator == (const Chord_find_successor_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const Chord_find_successor_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_find_successor_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Chord_find_successor_presult__isset {
  _Chord_find_successor_presult__isset() : success(false) {}
  bool success;
} _Chord_find_successor_presult__isset;

class Chord_find_successor_presult {
 public:


  virtual ~Chord_find_successor_presult() throw() {}

  successor* success;

  _Chord_find_successor_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _Chord_find_predecessor_args__isset {
  _Chord_find_predecessor_args__isset() : pid(false) {}
  bool pid;
} _Chord_find_predecessor_args__isset;

class Chord_find_predecessor_args {
 public:

  Chord_find_predecessor_args() : pid(0) {
  }

  virtual ~Chord_find_predecessor_args() throw() {}

  int32_t pid;

  _Chord_find_predecessor_args__isset __isset;

  void __set_pid(const int32_t val) {
    pid = val;
  }

  bool operator == (const Chord_find_predecessor_args & rhs) const
  {
    if (!(pid == rhs.pid))
      return false;
    return true;
  }
  bool operator != (const Chord_find_predecessor_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_find_predecessor_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_find_predecessor_pargs {
 public:


  virtual ~Chord_find_predecessor_pargs() throw() {}

  const int32_t* pid;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Chord_find_predecessor_result__isset {
  _Chord_find_predecessor_result__isset() : success(false) {}
  bool success;
} _Chord_find_predecessor_result__isset;

class Chord_find_predecessor_result {
 public:

  Chord_find_predecessor_result() {
  }

  virtual ~Chord_find_predecessor_result() throw() {}

  neighbor success;

  _Chord_find_predecessor_result__isset __isset;

  void __set_success(const neighbor& val) {
    success = val;
  }

  bool operator == (const Chord_find_predecessor_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const Chord_find_predecessor_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_find_predecessor_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Chord_find_predecessor_presult__isset {
  _Chord_find_predecessor_presult__isset() : success(false) {}
  bool success;
} _Chord_find_predecessor_presult__isset;

class Chord_find_predecessor_presult {
 public:


  virtual ~Chord_find_predecessor_presult() throw() {}

  neighbor* success;

  _Chord_find_predecessor_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _Chord_closest_preceding_finger_args__isset {
  _Chord_closest_preceding_finger_args__isset() : pid(false) {}
  bool pid;
} _Chord_closest_preceding_finger_args__isset;

class Chord_closest_preceding_finger_args {
 public:

  Chord_closest_preceding_finger_args() : pid(0) {
  }

  virtual ~Chord_closest_preceding_finger_args() throw() {}

  int32_t pid;

  _Chord_closest_preceding_finger_args__isset __isset;

  void __set_pid(const int32_t val) {
    pid = val;
  }

  bool operator == (const Chord_closest_preceding_finger_args & rhs) const
  {
    if (!(pid == rhs.pid))
      return false;
    return true;
  }
  bool operator != (const Chord_closest_preceding_finger_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_closest_preceding_finger_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_closest_preceding_finger_pargs {
 public:


  virtual ~Chord_closest_preceding_finger_pargs() throw() {}

  const int32_t* pid;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Chord_closest_preceding_finger_result__isset {
  _Chord_closest_preceding_finger_result__isset() : success(false) {}
  bool success;
} _Chord_closest_preceding_finger_result__isset;

class Chord_closest_preceding_finger_result {
 public:

  Chord_closest_preceding_finger_result() {
  }

  virtual ~Chord_closest_preceding_finger_result() throw() {}

  neighbor success;

  _Chord_closest_preceding_finger_result__isset __isset;

  void __set_success(const neighbor& val) {
    success = val;
  }

  bool operator == (const Chord_closest_preceding_finger_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const Chord_closest_preceding_finger_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_closest_preceding_finger_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Chord_closest_preceding_finger_presult__isset {
  _Chord_closest_preceding_finger_presult__isset() : success(false) {}
  bool success;
} _Chord_closest_preceding_finger_presult__isset;

class Chord_closest_preceding_finger_presult {
 public:


  virtual ~Chord_closest_preceding_finger_presult() throw() {}

  neighbor* success;

  _Chord_closest_preceding_finger_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};


class Chord_get_info_args {
 public:

  Chord_get_info_args() {
  }

  virtual ~Chord_get_info_args() throw() {}


  bool operator == (const Chord_get_info_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const Chord_get_info_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_get_info_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Chord_get_info_pargs {
 public:


  virtual ~Chord_get_info_pargs() throw() {}


  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Chord_get_info_result__isset {
  _Chord_get_info_result__isset() : success(false) {}
  bool success;
} _Chord_get_info_result__isset;

class Chord_get_info_result {
 public:

  Chord_get_info_result() {
  }

  virtual ~Chord_get_info_result() throw() {}

  neighbor success;

  _Chord_get_info_result__isset __isset;

  void __set_success(const neighbor& val) {
    success = val;
  }

  bool operator == (const Chord_get_info_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const Chord_get_info_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Chord_get_info_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Chord_get_info_presult__isset {
  _Chord_get_info_presult__isset() : success(false) {}
  bool success;
} _Chord_get_info_presult__isset;

class Chord_get_info_presult {
 public:


  virtual ~Chord_get_info_presult() throw() {}

  neighbor* success;

  _Chord_get_info_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class ChordClient : virtual public ChordIf {
 public:
  ChordClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) :
    piprot_(prot),
    poprot_(prot) {
    iprot_ = prot.get();
    oprot_ = prot.get();
  }
  ChordClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) :
    piprot_(iprot),
    poprot_(oprot) {
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void add_node();
  void send_add_node();
  void recv_add_node();
  void add_file();
  void send_add_file();
  void recv_add_file();
  void del_file();
  void send_del_file();
  void recv_del_file();
  void get_file();
  void send_get_file();
  void recv_get_file();
  void get_table();
  void send_get_table();
  void recv_get_table();
  void join_network(successor& _return, const int32_t pid);
  void send_join_network(const int32_t pid);
  void recv_join_network(successor& _return);
  void current_pred(predecessor& _return);
  void send_current_pred();
  void recv_current_pred(predecessor& _return);
  void notify(const int32_t pid, const int32_t new_port);
  void send_notify(const int32_t pid, const int32_t new_port);
  void recv_notify();
  void find_successor(successor& _return, const int32_t pid);
  void send_find_successor(const int32_t pid);
  void recv_find_successor(successor& _return);
  void find_predecessor(neighbor& _return, const int32_t pid);
  void send_find_predecessor(const int32_t pid);
  void recv_find_predecessor(neighbor& _return);
  void closest_preceding_finger(neighbor& _return, const int32_t pid);
  void send_closest_preceding_finger(const int32_t pid);
  void recv_closest_preceding_finger(neighbor& _return);
  void get_info(neighbor& _return);
  void send_get_info();
  void recv_get_info(neighbor& _return);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class ChordProcessor : public ::apache::thrift::TProcessor {
 protected:
  boost::shared_ptr<ChordIf> iface_;
  virtual bool process_fn(apache::thrift::protocol::TProtocol* iprot, apache::thrift::protocol::TProtocol* oprot, std::string& fname, int32_t seqid, void* callContext);
 private:
  std::map<std::string, void (ChordProcessor::*)(int32_t, apache::thrift::protocol::TProtocol*, apache::thrift::protocol::TProtocol*, void*)> processMap_;
  void process_add_node(int32_t seqid, apache::thrift::protocol::TProtocol* iprot, apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_add_file(int32_t seqid, apache::thrift::protocol::TProtocol* iprot, apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_del_file(int32_t seqid, apache::thrift::protocol::TProtocol* iprot, apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_get_file(int32_t seqid, apache::thrift::protocol::TProtocol* iprot, apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_get_table(int32_t seqid, apache::thrift::protocol::TProtocol* iprot, apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_join_network(int32_t seqid, apache::thrift::protocol::TProtocol* iprot, apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_current_pred(int32_t seqid, apache::thrift::protocol::TProtocol* iprot, apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_notify(int32_t seqid, apache::thrift::protocol::TProtocol* iprot, apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_find_successor(int32_t seqid, apache::thrift::protocol::TProtocol* iprot, apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_find_predecessor(int32_t seqid, apache::thrift::protocol::TProtocol* iprot, apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_closest_preceding_finger(int32_t seqid, apache::thrift::protocol::TProtocol* iprot, apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_get_info(int32_t seqid, apache::thrift::protocol::TProtocol* iprot, apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  ChordProcessor(boost::shared_ptr<ChordIf> iface) :
    iface_(iface) {
    processMap_["add_node"] = &ChordProcessor::process_add_node;
    processMap_["add_file"] = &ChordProcessor::process_add_file;
    processMap_["del_file"] = &ChordProcessor::process_del_file;
    processMap_["get_file"] = &ChordProcessor::process_get_file;
    processMap_["get_table"] = &ChordProcessor::process_get_table;
    processMap_["join_network"] = &ChordProcessor::process_join_network;
    processMap_["current_pred"] = &ChordProcessor::process_current_pred;
    processMap_["notify"] = &ChordProcessor::process_notify;
    processMap_["find_successor"] = &ChordProcessor::process_find_successor;
    processMap_["find_predecessor"] = &ChordProcessor::process_find_predecessor;
    processMap_["closest_preceding_finger"] = &ChordProcessor::process_closest_preceding_finger;
    processMap_["get_info"] = &ChordProcessor::process_get_info;
  }

  virtual bool process(boost::shared_ptr<apache::thrift::protocol::TProtocol> piprot, boost::shared_ptr<apache::thrift::protocol::TProtocol> poprot, void* callContext);
  virtual ~ChordProcessor() {}
};

class ChordProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  ChordProcessorFactory(const ::boost::shared_ptr< ChordIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< ChordIfFactory > handlerFactory_;
};

class ChordMultiface : virtual public ChordIf {
 public:
  ChordMultiface(std::vector<boost::shared_ptr<ChordIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~ChordMultiface() {}
 protected:
  std::vector<boost::shared_ptr<ChordIf> > ifaces_;
  ChordMultiface() {}
  void add(boost::shared_ptr<ChordIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void add_node() {
    size_t sz = ifaces_.size();
    for (size_t i = 0; i < sz; ++i) {
      ifaces_[i]->add_node();
    }
  }

  void add_file() {
    size_t sz = ifaces_.size();
    for (size_t i = 0; i < sz; ++i) {
      ifaces_[i]->add_file();
    }
  }

  void del_file() {
    size_t sz = ifaces_.size();
    for (size_t i = 0; i < sz; ++i) {
      ifaces_[i]->del_file();
    }
  }

  void get_file() {
    size_t sz = ifaces_.size();
    for (size_t i = 0; i < sz; ++i) {
      ifaces_[i]->get_file();
    }
  }

  void get_table() {
    size_t sz = ifaces_.size();
    for (size_t i = 0; i < sz; ++i) {
      ifaces_[i]->get_table();
    }
  }

  void join_network(successor& _return, const int32_t pid) {
    size_t sz = ifaces_.size();
    for (size_t i = 0; i < sz; ++i) {
      if (i == sz - 1) {
        ifaces_[i]->join_network(_return, pid);
        return;
      } else {
        ifaces_[i]->join_network(_return, pid);
      }
    }
  }

  void current_pred(predecessor& _return) {
    size_t sz = ifaces_.size();
    for (size_t i = 0; i < sz; ++i) {
      if (i == sz - 1) {
        ifaces_[i]->current_pred(_return);
        return;
      } else {
        ifaces_[i]->current_pred(_return);
      }
    }
  }

  void notify(const int32_t pid, const int32_t new_port) {
    size_t sz = ifaces_.size();
    for (size_t i = 0; i < sz; ++i) {
      ifaces_[i]->notify(pid, new_port);
    }
  }

  void find_successor(successor& _return, const int32_t pid) {
    size_t sz = ifaces_.size();
    for (size_t i = 0; i < sz; ++i) {
      if (i == sz - 1) {
        ifaces_[i]->find_successor(_return, pid);
        return;
      } else {
        ifaces_[i]->find_successor(_return, pid);
      }
    }
  }

  void find_predecessor(neighbor& _return, const int32_t pid) {
    size_t sz = ifaces_.size();
    for (size_t i = 0; i < sz; ++i) {
      if (i == sz - 1) {
        ifaces_[i]->find_predecessor(_return, pid);
        return;
      } else {
        ifaces_[i]->find_predecessor(_return, pid);
      }
    }
  }

  void closest_preceding_finger(neighbor& _return, const int32_t pid) {
    size_t sz = ifaces_.size();
    for (size_t i = 0; i < sz; ++i) {
      if (i == sz - 1) {
        ifaces_[i]->closest_preceding_finger(_return, pid);
        return;
      } else {
        ifaces_[i]->closest_preceding_finger(_return, pid);
      }
    }
  }

  void get_info(neighbor& _return) {
    size_t sz = ifaces_.size();
    for (size_t i = 0; i < sz; ++i) {
      if (i == sz - 1) {
        ifaces_[i]->get_info(_return);
        return;
      } else {
        ifaces_[i]->get_info(_return);
      }
    }
  }

};

} // namespace

#endif
