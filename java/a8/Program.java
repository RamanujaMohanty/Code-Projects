package bytecode;

import java.util.*;

import bytecode.instructions.*;

public class Program {
    private final List<Instruction> instructions = new ArrayList<>();

    // label -> absolute ip (index into `instructions`) where that label sits
    private final Map<String, Integer> labels = new HashMap<>();
    // label -> list of branch instruction indices that are waiting to be patched
    private final Map<String, List<Integer>> fixups = new HashMap<>();

    public Program emit(Instruction instruction) {
        int ip = this.instructions.size();
        this.instructions.add(instruction);

        if (instruction instanceof Label lbl) {
            // when a Label is emitted, bind it immediately at this ip
            bindLabel(lbl.getValue(), ip);

        } else if (instruction instanceof BranchInstruction br) {
            // if we already know the target label, patch immediately
            Integer target = labels.get(br.getTargetLabel());
            if (target != null) {
                br.setTargetIp(target); // <-- use the label's ip (NOT the branch ip)
            } else {
                // otherwise, queue this branch index for later fixup
                fixups.computeIfAbsent(br.getTargetLabel(), k -> new ArrayList<>()).add(ip);
            }
        }

        return this;
    }

    /** Bind a label to a specific ip and patch any waiting branches. */
    private void bindLabel(String label, int ip) {
        // defend against duplicate labels:
        if (labels.containsKey(label)) {
            throw new IllegalStateException("Duplicate label bound: " + label);
        }

        labels.put(label, ip);

        List<Integer> pending = fixups.remove(label);
        if (pending != null) {
            for (int branchIdx : pending) {
                BranchInstruction br = (BranchInstruction) instructions.get(branchIdx);
                br.setTargetIp(ip);
            }
        }
    }

    /** Call this after codegen if you want a safety check. */
    public void assertNoUnresolvedBranches() {
        if (!fixups.isEmpty()) {
            throw new IllegalStateException("Unresolved branches for labels: " + fixups.keySet());
        }
    }

    public Instruction get(int i) {
        return instructions.get(i);
    }

    public int size() {
        return instructions.size();
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < instructions.size(); i++) {
            Instruction instruction = instructions.get(i);

            if (i > 0) {
                sb.append(System.lineSeparator());
            }

            if (instruction instanceof Label label) {
                sb.append(String.format("%03d: %s:", i, label.getValue()));
                continue;
            }

            String line = String.format("%03d: %s", i, instruction.toString().trim());

            if (instruction instanceof BranchInstruction branch) {
                String target = branch.isResolved() ? String.format("%03d", branch.getTargetIp()) : "???";
                line = String.format("%s  ; -> %s", line, target);
            }

            sb.append(line);
        }

        return sb.toString();
    }
}
