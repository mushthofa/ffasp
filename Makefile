.PHONY: clean All

All:
	@echo "----------Building project:[ ffasp - Debug ]----------"
	@"$(MAKE)" -f  "ffasp.mk"
clean:
	@echo "----------Cleaning project:[ ffasp - Debug ]----------"
	@"$(MAKE)" -f  "ffasp.mk" clean
