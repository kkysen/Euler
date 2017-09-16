//
// Created by kkyse on 9/15/2017.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define NUM_PROBLEMS 599

typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned long long ull;

typedef long long answer_t;

typedef answer_t (*const SolutionFunc)();

typedef struct Solution {
    const SolutionFunc solution;
    const uint num;
    const char *const name;
} Solution;

typedef struct Euler {
    uint num_solutions;
    Solution *const solutions;
} Euler;

Euler *new_euler() {
    Euler local_euler = {0, (Solution *) malloc(sizeof(Solution) * NUM_PROBLEMS)};
    Euler *euler = (Euler *) malloc(sizeof(Euler));
    memcpy(euler, &local_euler, sizeof(Euler));
    return euler;
}

void free_euler(Euler *const euler) {
    free(euler->solutions);
    free(euler);
}

void register_solution(Euler *const euler, const uint problem_num, const SolutionFunc solution_func,
                       const char *const name) {
    if (euler->num_solutions == NUM_PROBLEMS) {
        printf("too many solutions");
        exit(1);
    }
    const Solution solution = {solution_func, problem_num, name};
    memcpy(euler->solutions + euler->num_solutions++, &solution, sizeof(Solution));
}

int solution_cmp(const Solution *const s1, const Solution *const s2) {
    return s1->num - s2->num;
}

/*
 * FIXME
 * I was planning on sorting the solutions based on their problem number,
 * but qsort messes up the function pointers somehow and causes seg faults.
 */
void sort_solutions(Euler *const euler) {
    qsort(euler->solutions, sizeof(Solution), euler->num_solutions, (const void *) solution_cmp);
}

answer_t run_solution(Euler *const euler, const uint index) {
    return euler->solutions[index].solution();
}

void run_solutions(Euler *const euler) {
    //sort_solutions(Euler);
    for (uint i = 0; i < euler->num_solutions; i++) {
        Solution solution = euler->solutions[i];
        const answer_t answer = solution.solution();
        if (answer < 0) {
            printf("Euler #%d: %s: unfinished\n", solution.num, solution.name);
        } else {
            printf("Euler #%d: %s: %lld\n", solution.num, solution.name, answer);
        }
    }
}

// Multiples of 3 and 5
answer_t euler1() {
    const uint MAX = 1000;
    uint sum = 0;
    for (uint i = 0; i < MAX; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            sum += i;
        }
    }
    return sum;
}

// Even Fibonacci Numbers
answer_t euler2() {
    const uint MAX = 10000000;
    uint sum = 0;
    uint a = 0;
    uint b = 1;
    uint temp;
    while (a < MAX) {
        if ((a & 1) == 0) {
            sum += a;
        }
        temp = a;
        a = b;
        b += temp;
    }
    return sum;
}

// Largest Prime Factor
answer_t euler3() {
    ull n = 600851475143ULL;
    for (ull i = 2ULL; i < n; i++) {
        while (n % i == 0) {
            n /= i;
        }
    }
    return n;
}

bool is_palindrome(uint i) {
    uint temp = i;
    uint reversed = 0;
    while (temp) {
        reversed = 10 * reversed + (temp % 10);
        temp /= 10;
    }
    return reversed == i;
}

int largest_palindrome_product(uint min, uint max) {
    uint answer = 0;
    for (uint i = max; i >= min; i--) {
        for (uint j = max; j >= min; j--) {
            const uint p = i * j;
            //printf("%d\n", p);
            if (p > answer && is_palindrome(p)) {
                answer = p;
            }
        }
    }
    return answer == 0 ? -1 : (int) answer;
}

// Largest Palindrome Product
answer_t euler4() {
    int answer = largest_palindrome_product(100, 999);
    if (answer == -1) {
        return -1;
    }
}

bool all_divisible(uint i) {
    for (uint j = 1; j <= 20; ++j) {
        if (i % j) {
            return false;
        }
    }
    return true;
}

// very slow, TODO optimize
// Smallest Multiple
answer_t euler5() {
    for (uint i = 1;; ++i) {
        if (all_divisible(i)) {
            return i;
        }
    }
}

uint sum_squares(uint n) {
    return (n * (n + 1) * ((n << 1) + 1)) / 6;
}

uint square_sums(uint n) {
    const uint sum = (n * (n + 1)) >> 1;
    return sum * sum;
}

// Sum Square Difference
answer_t euler6() {
    const uint n = 100;
    return square_sums(n) - sum_squares(n);
}

// TODO finish
// 10001st Prime
answer_t euler7() {
    const uint n = 10001;
    uint i;
    uint prime;
    for (prime = 3, i = 0; i <= n; ++i, prime += 2) {
    
    }
    
    return -1;
}

ull parse_ull(const char *bits, const uint from, const uint to) {
    ull n = 0;
    for (uint i = from; i < to; ++i) {
        n = n * 10 + bits[i];
    }
    return n;
}

// Largest Product in a Series
answer_t euler8() {
    const char *num_str = ""
            "73167176531330624919225119674426574742355349194934"
            "96983520312774506326239578318016984801869478851843"
            "85861560789112949495459501737958331952853208805511"
            "12540698747158523863050715693290963295227443043557"
            "66896648950445244523161731856403098711121722383113"
            "62229893423380308135336276614282806444486645238749"
            "30358907296290491560440772390713810515859307960866"
            "70172427121883998797908792274921901699720888093776"
            "65727333001053367881220235421809751254540594752243"
            "52584907711670556013604839586446706324415722155397"
            "53697817977846174064955149290862569321978468622482"
            "83972241375657056057490261407972968652414535100474"
            "82166370484403199890008895243450658541227588666881"
            "16427171479924442928230863465674813919123162824586"
            "17866458359124566529476545682848912883142607690042"
            "24219022671055626321111109370544217506941658960408"
            "07198403850962455444362981230987879927244284909188"
            "84580156166097919133875499200524063689912560717606"
            "05886116467109405077541002256983155200055935729725"
            "71636269561882670428252483600823257530420752963450";
    const uint num_adjacent = 13;
    const uint num_digits = (uint) strlen(num_str);
    char *const num = (char *) malloc(num_digits * sizeof(char));
    for (uint i = 0; i < num_digits; ++i) {
        num[i] = num_str[i] - (char) '0';
    }
    
    // could keep running product and divide last and multiply new digit
    // but then have to deal with zeroes
    // since the number isn't that long, this is simpler
    ull max = 0;
    for (uint i = 0; i < num_digits - num_adjacent; ++i) {
        ull n = 1;
        for (uint j = 0; j < num_adjacent; ++j) {
            n *= num[i + j];
        }
        if (n > max) {
            max = n;
        }
    }
    
    return max;
}

// Special Pythagorean Triplet
answer_t euler9() {
    const uint SUM = 1000;
    const uint MAX_MN = 100;
    for (uint n = 1; n < MAX_MN; ++n) {
        for (uint m = n + 1; m < MAX_MN; ++m) {
            const uint mm = m * m;
            const uint nn = n * n;
            const uint a = mm - nn;
            const uint b = (m * n) << 1;
            const uint c = mm + nn;
            if (a + b + c == SUM) {
                //printf("%u, %u\n", n, m);
                //printf("%u, %u, %u\n", a, b, c);
                return a * b * c;
            }
        }
    }
    return -1;
}

// TODO finish
// Summation of Primes
answer_t euler10() {
    return -1;
}

typedef enum Month {
    January = 1, February, March, April, May, June, July, August, September, October, November, December
} Month;

typedef enum DayOfWeek {
    Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday
} DayOfWeek;

const DayOfWeek DAYS_OF_WEEK[7] = {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};

DayOfWeek day_of_week(const byte d, const Month m, uint y) {
    y -= m < 3;
    return (DayOfWeek) ((y + y / 4 - y / 100 + y / 400 + "-bed=pen+mad."[m] + d) % 7);
}

typedef struct Date {
    const byte day;
    const byte month;
    const uint year;
} Date;

uint num_sundays_on_first_of_month(Date start, Date end) {
    uint num_sundays = 0;
    for (uint year = start.year; year < end.year; ++year) {
        for (Month month = January; month < December; ++month) {
            if (day_of_week(1, month, year) == Sunday) {
                num_sundays++;
            }
        }
    }
    return num_sundays;
}

// Counting Sundays
answer_t euler19() {
    Date start = {1, January, 1901};
    Date end = {31, December, 2000};
    return num_sundays_on_first_of_month(start, end);
}

#define EULER(n, name) register_solution(euler, n, euler##n, name)

void register_solutions(Euler *const euler) {
    EULER(1, "Multiples of 3 and 5");
    EULER(2, "Even Fibonacci Numbers");
    EULER(3, "Largest Prime Factor");
    EULER(4, "Largest Palindrome Product");
    EULER(5, "Smallest Multiple");
    EULER(6, "Sum Square Difference");
    EULER(7, "10001st Prime");
    EULER(8, "Largest Product in a Series");
    EULER(9, "Special Pythagorean Triplet");
    EULER(10, "Summation of Primes");
    
    EULER(19, "Counting Sundays");
}

int main() {
    Euler *const euler = new_euler();
    register_solutions(euler);
    run_solutions(euler);
    free_euler(euler);
    printf("\nall done\n");
    return 0;
}