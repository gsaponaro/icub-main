#IRpcServer.thrift

/**
* IRpcServer
*
* Interface for an example module. 
*/

service IRpcServer {

  /**
  * Get answer from server
  * @return the answer
  */
  i32 get_answer();
  
  /**
  * Set value for future answers.
  * @param rightAnswer new answer
  * @return true if connection was successful
  */
  bool set_answer(1:i32 rightAnswer)
  
  /**
  * Add one integet to future answers.
  * @param x value to add
  * @return new value
  */
  i32 add_one(1:i32 x);

  /** 
  * Start service
  * @return true if service started correctly
  */
  bool start();

  /** 
  * Stop service
  * @return true if service stopped correctly
  */
  bool stop();

  /** 
  * Check is service is running
  * @return true/false if service is/is not running 
  */
  bool is_running();
}
