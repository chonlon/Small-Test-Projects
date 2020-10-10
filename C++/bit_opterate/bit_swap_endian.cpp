// compile-time endianness swap based on http://stackoverflow.com/a/36937049 
template<class T, std::size_t... N>
constexpr T bswap_impl(T i, std::index_sequence<N...>) {
  return (((i >> N*CHAR_BIT & std::uint8_t(-1)) << (sizeof(T)-1-N)*CHAR_BIT) | ...);
}
template<class T, class U = std::make_unsigned_t<T>>
constexpr U bswap(T i) {
  return bswap_impl<U>(i, std::make_index_sequence<sizeof(T)>{});
}
 
int main()
{
    static_assert(bswap<std::uint16_t>(0x1234u)==0x3412u);
    static_assert(bswap<std::uint64_t>(0x0123456789abcdefULL)==0xefcdab8967452301ULL);
}