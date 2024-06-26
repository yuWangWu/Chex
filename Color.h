#pragma once

class Color {
public:
	unsigned char r = 255, g = 255, b = 255;

public:
	bool operator==(Color c) {
		if ((r == c.r) && (g == c.g) && (b == c.b))
			return true;
		return false;
	}
	bool operator!=(Color c) {
		return !operator==(c);
	}
};