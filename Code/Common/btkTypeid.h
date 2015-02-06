/* 
 * The Biomechanical ToolKit
 * Copyright (c) 2009-2015, Arnaud Barré
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *     * Redistributions of source code must retain the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *     * Neither the name(s) of the copyright holders nor the names
 *       of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __btkTypeid_h
#define __btkTypeid_h

namespace btk
{
  class typeid_t
  {
  public:
    typeid_t() = delete;
    ~typeid_t() noexcept = default;
    typeid_t(const typeid_t& ) = default;
    typeid_t(typeid_t&& ) noexcept = default;
    typeid_t& operator=(const typeid_t& ) = default;
    typeid_t& operator=(typeid_t&& ) noexcept = default;
    
    explicit operator size_t() const noexcept {return reinterpret_cast<size_t>(this->id);};
    
    friend constexpr bool operator==(typeid_t lhs, typeid_t rhs) noexcept {return (lhs.id == rhs.id);};
    friend constexpr bool operator!=(typeid_t lhs, typeid_t rhs) noexcept {return (lhs.id != rhs.id);};
    
  private:
    template<typename T> friend constexpr typeid_t static_typeid() noexcept;
    
    using sig = typeid_t();
    sig* id;
    
    constexpr typeid_t(sig* id) : id{id} {};
  };

  template<typename T>
  constexpr inline typeid_t static_typeid() noexcept
  {
    return &static_typeid<T>;
  };
  
  /**
   * @class typeid_t btkTypeid.h
   * @brief Unique identifier for each type without using runtime type identifier
   *
   * Internally, and compared to the RTTI mechanism, this class use the so-called one-definition rule (ODR).
   * @par Reference
   * [...] If an identifier declared with external linkage is used in an expression [...], somewhere in the entire program there shall be exactly one external definition for the identifier; [...]
   *
   * Largely inspired by http://codereview.stackexchange.com/questions/48594/unique-type-id-no-rtti
   */
  
  /**
   * @fn template<typename T> constexpr typeid_t static_typeid() noexcept
   * Returns the identifier associated with the given template type
   */
}

#endif // __btkTypeid_h