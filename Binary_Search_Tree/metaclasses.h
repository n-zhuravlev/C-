#ifndef SEARCHTREE_METACLASSES_H
#define SEARCHTREE_METACLASSES_H

// define metaclasses for compare operations 
// all metaclasses defined in nested namespace btree::meta

#include <type_traits>

namespace btree {

	namespace meta {

		// class has operator <
		template<typename T>
		struct has_lt
		{
		private:

			static void detect(...);

			template<typename U>
			static decltype(static_cast<bool>(std::declval<U>() < std::declval<U>())) detect(const U &);

		public:

			static constexpr bool value = std::is_same<bool, decltype(detect(std::declval<T>()))>::value;
		};


		// class has operator >
		template<typename T>
		struct has_gt
		{
		private:

			static void detect(...);

			template<typename U>
			static decltype(static_cast<bool>(std::declval<U>() > std::declval<U>())) detect(const U &);

		public:

			static constexpr bool value = std::is_same<bool, decltype(detect(std::declval<T>()))>::value;
		};


		// class has operator ==
		template<typename T>
		struct has_eq
		{
		private:

			static void detect(...);

			template<typename U>
			static decltype(static_cast<bool>(std::declval<U>() == std::declval<U>())) detect(const U &);

		public:

			static constexpr bool value = std::is_same<bool, decltype(detect(std::declval<T>()))>::value;
		};


		// class has operator !=
		template<typename T>
		struct has_neq
		{
		private:

			static void detect(...);

			template<typename U>
			static decltype(static_cast<bool>(std::declval<U>() != std::declval<U>())) detect(const U &);

		public:

			static constexpr bool value = std::is_same<bool, decltype(detect(std::declval<T>()))>::value;
		};


		// class has operator < and operator ==
		template<typename T>
		struct has_lt_eq
		{
		public:
			static constexpr bool value = (has_lt<T>::value && has_eq<T>::value);
		};


		// class has operator < and operator !=
		template<typename T>
		struct has_lt_neq
		{
		public:
			static constexpr bool value = (has_lt<T>::value && !has_eq<T>::value && has_neq<T>::value);
		};


		// class has operator > and operator ==
		template<typename T>
		struct has_gt_eq
		{
		public:
			static constexpr bool value = (!has_lt<T>::value && has_gt<T>::value && has_eq<T>::value);
		};


		// class has operator > and operator !=
		template<typename T>
		struct has_gt_neq
		{
		public:
			static constexpr bool value = (!has_lt<T>::value && has_gt<T>::value && !has_eq<T>::value && has_neq<T>::value);
		};


		// class hasn't operator < and operator >
		// or class hasn't operator == and operator !=
		template<typename T>
		struct has_nothing
		{
		public:
			static constexpr bool value = (!has_lt_eq<T>::value && !has_lt_neq<T>::value && !has_gt_eq<T>::value && !has_gt_neq<T>::value);
		};

	}

}

#endif //SEARCHTREE_METACLASSES_H