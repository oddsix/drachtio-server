/*
Copyright (c) 2015, David C Horton

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include <assert.h>

#include "newrelic_transaction.h"
#include "newrelic_common.h"


#include "nr-transaction.hpp"
#include "controller.hpp"

namespace drachtio {

  NrTransaction::NrTransaction(const char* szName) : m_name(szName), m_txnId( newrelic_transaction_begin() ) {
    if( NULL != szName ) {
      newrelic_transaction_set_name(m_txnId, szName); 
    }
  }

  NrTransaction::~NrTransaction() {
    if( 0 != m_txnId ) {
      assert( m_name.length() > 0 ) ;
      int error_code = newrelic_transaction_end(m_txnId);
    }
  }
  void NrTransaction::setName(const char* szName) { 
    m_name = szName;
    newrelic_transaction_set_name(m_txnId, szName); 
  }

  void NrTransaction::endTransaction() {
    assert( m_name.length() > 0 ) ;
    int error_code = newrelic_transaction_end(m_txnId);
    m_txnId = 0 ;    
  }

}

