/**
 * @param {number[]} nums
 * @return {void} Do not return anything, modify nums in-place instead.
 */
var moveZeroes = function (nums) {
    console.log(nums);

    var insertZero = function (startZeroIdx, endZeroIdx, lastNoneZeroIdx) {
        // console.log('--insert', startZeroIdx, endZeroIdx, lastNoneZeroIdx);
        // console.log(nums);

        let moveNum = lastNoneZeroIdx - endZeroIdx;

        let i = 0;
        while (i < moveNum) {
            nums[startZeroIdx + i] = nums[endZeroIdx + i + 1];
            i++;
        }

        let zeroNum = endZeroIdx - startZeroIdx + 1;

        i = 0;
        while(i < zeroNum) {
            nums[startZeroIdx+i+moveNum] = 0;
            i++;
        }
    }

    let len = nums.length;

    // 最后一个非0数字索引
    var lastNoneZeroIdx = len - 1;
    while (lastNoneZeroIdx >= 0) {
        if (nums[lastNoneZeroIdx] == 0) {
            lastNoneZeroIdx--;
            continue;
        }
        else {
            break;
        }
    }

    // console.log('lastNoneZeroIdx', lastNoneZeroIdx)

    let idx = 0;
    while (idx < len) {
        if (nums[idx] == 0 ) {
            if (idx < lastNoneZeroIdx) {

                let tmpIdx = idx;
                while (nums[tmpIdx] == 0) {
                    tmpIdx++;
                }

                insertZero(idx, tmpIdx-1, lastNoneZeroIdx);

                // console.log(nums);
                
                lastNoneZeroIdx = lastNoneZeroIdx - (tmpIdx - idx);

                // console.log('lastNoneZeroIdx', lastNoneZeroIdx);
            }
        }
        else {
            if (idx >= lastNoneZeroIdx) {
                break;
            }
        }

        idx++;
    }

    return nums;
};


// var case1 = [0, 1, 0, 3, 12];
// [1,3,12,0,0]

// var case1 = [1, 0, 3, 12, 0, 0];

// var case1 = [1, 0, 0, 0, 0, 0, 0, 0, 0, 0];

var case1 = [4, 2, 4, 0, 0, 3, 0, 5, 1, 0];

var res = moveZeroes(case1);

console.log(res);