import (
	"sort"
)

func minCost(basket1 []int, basket2 []int) int64 {
	freq := make(map[int]int)
	for _, num := range basket1 {
		freq[num]++
	}
	for _, num := range basket2 {
		freq[num]--
	}

	var swaps []int
	minVal := 1 << 30
	for num, cnt := range freq {
		if cnt%2 != 0 {
			return -1
		}
		times := abs(cnt) / 2
		for i := 0; i < times; i++ {
			swaps = append(swaps, num)
		}
		if num < minVal {
			minVal = num
		}
	}

	sort.Ints(swaps)

	var res int64
	n := len(swaps)
	for i := 0; i < n/2; i++ {
		if swaps[i] < 2*minVal {
			res += int64(swaps[i])
		} else {
			res += int64(2 * minVal)
		}
	}

	return res
}

func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}